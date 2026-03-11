#include "scheduler.h"


bool AllQueuesEmpty(std::vector<Queue>& queues){
    for (auto& q : queues){
        if(!q.processes.empty()) return false;
    }
    return true;
}

void loadNewProcesses(const int& curTime, std::vector<Queue>& queues, std::vector<Process>& Processes) {
    for (auto &i : Processes) {
        if (i.arrivalTime == curTime && !i.isLoaded) {
            // Truy cập vào queue rồi push process vào queue đó
            addProcessToQueue(i, queues);
            i.isLoaded = true;
        }
    }
}

void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses, Logger& logs){
    //Dừng chạy khi số lượng process đã hoàn thành = total process
    int countProcess = 0;
    int curTime = 0;
    int Qidx = 0; //Q1,Q2,Q3
    int TotalProcess = allProcesses.size();
    //Timeslice còn lại của từng queue
    int TSliceLeft = 0;
    bool isBusy = false; //Dùng để phân biệt SJF & SRTN

    //Kiểm tra điều kiện dừng
    while (countProcess < TotalProcess)
    {
        //Nạp các process dựa trên thời gian arrivalTime mỗi giây curTime
        loadNewProcesses(curTime,queues,allProcesses);

        //Kiểm tra TS còn không và queue hiện tại có process nào không, nếu không thì chuyển sang queue tiếp theo
        if (TSliceLeft <= 0 || queues[Qidx].processes.empty())
        {
                //Chuyển tiến trình Qidx ngay vì đã thỏa điều kiện chuyển Queue là tslice hết hoặc empty
                Qidx = (Qidx + 1) % queues.size();

                //Nếu queue mới chuyển sang rỗng thì tiếp tục chuyển sang queue tiếp theo
                int countQueue = 0;
                while (queues[Qidx].processes.empty() && countQueue < queues.size()) {
                    Qidx = (Qidx + 1) % queues.size();
                    countQueue++;
                }

                //Check nếu tất cả queue trống thì tăng curTime và tiếp tục vòng lặp để load process mới vào queue
                if (AllQueuesEmpty(queues)) {
                    curTime++;
                    continue; 
                }
                else{
                    //Chỉ lấy TS khi đã sang queue mới
                    TSliceLeft = queues[Qidx].timeSlice;
                    //SJF: Nếu mà đang dùng nhưng hết timeslice thì đặt lại thành false để tiếp tục sort mới
                    //Tại vì có thể có tiến trình mới vào Queue này lúc đang hết timeslice
                    isBusy = false;
                }
        }
        
        //Tạo biến để code clean
        Queue& curQ = queues[Qidx];

        //Kiểm tra Policy của Qidx hiện tại
        if (queues[Qidx].policy == "SRTN"){
            sortProcessesBySRTN(curQ.processes);
        }
        //Kiểm tra process chạy xong chưa rồi mới sort
        else{
            if (!isBusy)
            {
                sortProcessesBySJF(curQ.processes);
                isBusy = true; //Khóa lại không cho sort cho đến khi hoàn thành
            }
        }

        //Tạo chương trình bằng chương trình đứng đầu trong queue
        Process& p = curQ.processes[0];

        //Ghi lại thời gian vào log
        logs.addLog(curTime,p.pid,p.queueId);
        
        p.remainingTime--;
        curTime++;
        TSliceLeft--;

        //Khi process hoàn thành thì cập nhật các thông số cần thiết và xóa process đó khỏi queue
        if (p.remainingTime == 0)
        {
            p.completionTime = curTime;
            p.turnAroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnAroundTime - p.burstTime;
            countProcess++;

            allProcesses[p.pid-1] = p; //Cập nhật lại process đã hoàn thành vào vector allProcess để in ra file cuối cùng
            removeCompletedProcesses(curQ);
        }
    }
}

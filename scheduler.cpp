#include "scheduler.h"


bool AllQueuesEmpty(std::vector<Queue>& queues){
    for (auto& q : queues){
        if(!q.processes.empty()) return false;
    }
    return true;
}

void loadNewProcesses(int curTime, std::vector<Queue>& queues, std::vector<Process>& Processes){
    for (auto &i : Processes){
            if (i.arrivalTime == curTime && !i.isLoaded)
            {
                //Truy cap vao queue roi pushback processes vao dung vi tri queue
                addProcessToQueue(i,queues);
                i.isLoaded = true;
            }
        }
}

void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses,Logger& logs){
    //Dung chay khi so luong process da hoan thanh = total
    int countProcess = 0;
    int curTime = 0;
    int Qidx = 0; //Q1,Q2,Q3
    int TotalProcess = allProcesses.size();
    //Day la timeslide thay doi theo tung queue
    int TSliceLeft = 0;
    bool isBusy = false; //Dung de phan biet policy srtn va sjf

    //Kiem tra dieu kien dung khi da hoan thanh tat ca cac process
    while (countProcess < TotalProcess)
    {
        //Nap cac process dua tren thoi gian arrivalTime moi giay curTime
        loadNewProcesses(curTime,queues,allProcesses);


        //Kiem tra queue Qidx co empty k va con timeslice k de chuyen qidx
        if (queues[Qidx].processes.empty() || TSliceLeft <= 0 )
        {
                //Kiem tra xem tat ca cac queues co empty k
                if (AllQueuesEmpty(queues))
                {
                    //Neu he thong khong co tien trinh
                    curTime++;
                    continue;
                }

            //Kiem tra tung queues xem co process nao trong hang doi k
            do
            {
                Qidx = (Qidx + 1) % queues.size();

            } while (queues[Qidx].processes.empty());
            
            //Neu da tim duoc queue Qidx thoa man thi lay timeslice cua cai do
            TSliceLeft = queues[Qidx].timeSlice;          
            //SJF: Neu ma dang dung nhung het timeslice thi dat lai thanh false de tiep tuc sort moi
            //Tai vi co the co tien trinh moi vao Queue nay luc b dang het timesliced
            isBusy = false;
        }
        
        //Tao bien cho code clean hon
        Queue& curQ = queues[Qidx];

        //kiem tra policy cua Qidx (hientai)
        if (queues[Qidx].policy == "SRTN"){
            sortProcessesBySRTN(curQ.processes);
        }
        //Phai kiem tra process chay xong chx roi ms sort
        else{
            if (!isBusy)
            {
                sortProcessesBySJF(curQ.processes);
                isBusy = true; // Khoa lai khong cho no sort den khi hoan thanh
            }
        }

        //Tao chuong trinh bang ctrinh dung dau trong queue
        Process& p = curQ.processes[0];

        //Ghi lai tg de co the in ra output
        logs.addLog(curTime,p.pid,p.queueId);
        
        p.remainingTime--;
        curTime++;
        TSliceLeft--;
        //neu thoi gian cua process = 0 tuong duong voi done process do va se lam process moi
        if (p.remainingTime == 0)
        {
            p.completionTime = curTime;
            p.turnAroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnAroundTime - p.burstTime;
            countProcess++;
            removeCompletedProcesses(curQ);
            isBusy = false; //Dat thanh false SJF co the qua Pid ke tiep
        }
        
    }
}

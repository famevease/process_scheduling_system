#include "scheduler.h"


bool QueuesIsEmpty(std::vector<Queue>& queues){
    for (auto& q : queues){
        if(!q.processes.empty()) return false;
    }
    return true;
}


void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses,Logger& logs){
    int countProcess = 0;
    int curTime = 0;
    int Qidx = 0; //Q1,Q2,Q3
    int TotalProcess = allProcesses.size();
    //Kiem tra dieu kien dung khi da hoan thanh tat ca cac process
    while (countProcess < TotalProcess)
    {
        //Nap cac process dua tren thoi gian arrivalTime
        for (auto &i : allProcesses){
            if (i.arrivalTime == curTime)
            {
                //Truy cap vao queue roi pushback processes vao dung vi tri queue
                addProcessToQueue(i,queues);
            }
            
        }
        //Queue current
        Queue& curQ = queues[Qidx];
        if (curQ.processes.empty())
        {
            Qidx = (Qidx + 1) / queues.size();
            //Neu tat ca hang queues deu kh con tien trinh
            if(QueuesIsEmpty(queues)){
                curTime++;
            }
        }

    
    int TSliceUsed = 0;
    while (TSliceUsed < curQ.timeSlice && !curQ.processes.empty())
        {   //kiem tra policy cua queues hien tai
            if (curQ.policy == "SRTN") sortProcessesBySRTN(curQ.processes);
            else sortProcessesBySJF(curQ.processes);

            //Nap tien trinh va so sanh lien tuc neu policy la STRN
            for (auto& p: allProcesses){
                if (p.arrivalTime == curTime) addProcessToQueue(p,queues);
            }

            Process& p = curQ.processes[0];
            logs.addLog(curTime,p.pid,p.queueId);
            p.remainingTime--;
            curTime++;
            TSliceUsed++;
            if (p.remainingTime == 0)
            {
                countProcess++;
                removeCompletedProcesses(curQ.processes);
            }

        }
    }
    
}

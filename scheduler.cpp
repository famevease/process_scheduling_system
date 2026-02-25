#include "scheduler.h"


bool QueuesIsEmpty(std::vector<Queue>& queues){

}


void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses){
    int countProcess = 0;
    int curTime = 0;
    int Qidx = 0; //Q1,Q2,Q3
    int TotalProcess = allProcesses.size();
    while (countProcess < TotalProcess)
    {
        for (auto &i : allProcesses){
            if (i.arrivalTime == curTime)
            {
                //Truy cap vao queue roi pushback processes vao dung vi tri queue
                queues[i.queueId].processes.push_back(i);
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
        while (TSliceUsed < curQ.timeSlice )
        {
            if (curQ.policy == "SRTN") sortProcessesBySRTN(curQ.processes);
            else sortProcessesBySRTN(curQ.processes);

            Process& p = curQ.processes[0];
            p.remainingTime--;
            curTime++;
            TSliceUsed++;
            if (p.remainingTime == 0)
            {
                countProcess++;
                //Xoa process da hoan thanh
                curQ.processes.erase(curQ.processes.begin());
            }
            
        }
        
        
        

    }
    
}

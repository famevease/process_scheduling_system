#ifndef components_h
#define components_h
#include <string>
#include <vector>
#include <algorithm>


struct Process{
    int pid; //p1,p2,...
    int arrivalTime;
    int burstTime; //tg can de hoan thanh
    int queueId;

    int remainingTime = burstTime; //tg con lai de chay xong ct
    int waitingTime = 0; //tg nam trong hang cho
    int turnAroundTime = 0;     //tu luc vao den luc xong (complete - arrival)
    int completionTime = 0; 

    bool isLoaded = false;
};

struct Queue{
    int qid;
    int timeSlice;
    std::string policy; // sjf & srtn
    std::vector<Process> processes = {};

    //Tra ve dia chi cua chuong trinh dau tien trong hang doi
    Process* getCurrentProcess() {
        if (processes.empty()) return nullptr;
        return &processes[0];
    }
};

void addProcessToQueue(const Process& process, std::vector<Queue>& queues);
void sortProcessesBySJF(std::vector<Process>& processes);
void sortProcessesBySRTN(std::vector<Process>& processes);
void removeCompletedProcesses(Queue& queue);
float averageWaitingTime(const std::vector<Process>& processes);
float averageTurnAroundTime(const std::vector<Process>& processes);

#endif
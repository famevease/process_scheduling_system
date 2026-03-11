#ifndef components_h
#define components_h
#include <string>
#include <vector>
#include <algorithm>


struct Process{
    int pid; 
    int arrivalTime;
    int burstTime; 
    int queueId;

    int remainingTime; 
    int waitingTime = 0; 
    int turnAroundTime = 0;
    int completionTime = 0; 

    bool isLoaded = false;
};

struct Queue{
    int qid;
    int timeSlice;
    std::string policy; // sjf & srtn
    std::vector<Process> processes = {};

    //Trả về process đầu tiên trong queue (process cần chạy)
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
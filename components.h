#ifndef components_h
#define components_h
#include <string>
#include <vector>

struct Process{
    int pid;
    int arrivalTime;
    int burstTime;
    int queueId;
    int remainingTime = burstTime;
    int waitingTime = 0;
    int turnAroundTime = 0;
    int completionTime = 0;
};

struct Queue{
    int qid;
    int timeSlice;
    std::string policy;
    std::vector<Process> processes = {};
    Process* currentProcess = processes.empty() ? nullptr : &processes[0];
};

void addProcessToQueue(const Process& process, std::vector<Queue>& queues);
void sortProcessesBySJF(std::vector<Process>& processes);
void sortProcessesBySRTN(std::vector<Process>& processes);
void removeCompletedProcesses(std::vector<Process>& processes);
#endif
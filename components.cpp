#include "components.h"

void addProcessToQueue(const Process& process, std::vector<Queue>& queues) {
    for (auto& queue : queues) {
        if (queue.qid == process.queueId) {
            queue.processes.push_back(process);
            return;
        }
    }
}

void sortProcessesBySJF(std::vector<Process>& processes) {
    int n = processes.size();
    if (n <= 1) {
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n - i - 1; j++) {
            if (processes[i].burstTime > processes[j].burstTime) {
                std::swap(processes[i], processes[j]);
            }
            else if (processes[i].burstTime == processes[j].burstTime) {
                if (processes[i].arrivalTime < processes[j].arrivalTime) {
                    std::swap(processes[i], processes[j]);
                }
            }
        }
    }
}

void sortProcessesBySRTN(std::vector<Process>& processes) {
    int n = processes.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n - i - 1; j++) {
            if (processes[i].remainingTime > processes[j].remainingTime) {
                std::swap(processes[i], processes[j]);
            }
            else if (processes[i].remainingTime == processes[j].remainingTime) {
                if (processes[i].waitingTime < processes[j].waitingTime) {
                    std::swap(processes[i], processes[j]);
                }
            }
        }
    }
}

void removeProcesses(std::vector<Process>& processes) {
    processes.erase(processes.begin());
}


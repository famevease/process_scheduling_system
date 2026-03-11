#include "file_handler.h"

void readFile(const std::string& filename, std::vector<Queue>& queues, std::vector<Process>& processes) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    char dummy; // Để chứa chữ 'Q' hoặc 'P'

    file >> line;
    int numQueues = std::stoi(line);
    while (numQueues--) {
        Queue queue;
        file >> dummy >> queue.qid >> queue.timeSlice >> queue.policy;
        queues.push_back(queue);
    }

    while (file >> dummy) {
        Process process;
        file >> process.pid >> process.arrivalTime >> process.burstTime >> dummy >> process.queueId;
        process.remainingTime = process.burstTime;
        processes.push_back(process);
    }
    file.close();
}

void writeOutput(const std::string& filename, const Logger& logger, const std::vector<Process>& processes) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    file << "================== CPU SCHEDULING DIAGRAM ==================\n";
    file << "\n[Start - End]\tQueue\tProcess\n";
    file << "------------------------------------------------------------\n";
    for (const auto& log : logger.Logs) {
        file << "[" << log.start << " - " << log.end << "]\t\t\tQ" << log.qid << "\t\tP" << log.pid << "\n";
    }
    file << "\n================ PROCESS STATISTICS ======================\n";
    file << "\nProcess\t\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    file << "------------------------------------------------------------\n";
    for (const auto& process : processes) {
        file << "P" << process.pid << "\t\t\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t\t" 
             << process.completionTime << "\t\t\t" << process.turnAroundTime << "\t\t\t" << process.waitingTime << "\n";
    }
    file << "------------------------------------------------------------\n";
    file << "Average Turnaround Time: " << averageTurnAroundTime(processes) << "\n";
    file << "Average Waiting Time: " << averageWaitingTime(processes) << "\n";
    file << "\n============================================================";
    file.close();
}
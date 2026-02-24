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
        processes.push_back(process);
    }
    file.close();
}
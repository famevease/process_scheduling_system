#include <iostream>
#include "file_handler.h"
#include "scheduler.h"

int main() {
    std::vector<Queue> queues; //nghiên cứu dùng queue/priority_queue thử
    std::vector<Process> processes; //dùng để lưu p1 -> p5 ban đầu (ch trong queue)
    Logger logger;
    
    readFile("input.txt", queues, processes);
    runSimulation(queues, processes, logger);
    writeOutput("output.txt", logger, processes);

    return 0;
}
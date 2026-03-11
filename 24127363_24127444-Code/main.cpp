#include <iostream>
#include "file_handler.h"
#include "scheduler.h"

int main(int argc, char* argv[]) {
    std::vector<Queue> queues; //dùng để lưu Q1,Q2,Q3
    std::vector<Process> processes; //dùng để lưu p1 -> p5 ban đầu (chưa trong queue)
    Logger logger;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    readFile(argv[1], queues, processes);
    runSimulation(queues, processes, logger);
    writeOutput(argv[2], logger, processes);

    return 0;
}
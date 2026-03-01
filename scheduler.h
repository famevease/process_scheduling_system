#ifndef scheduler_h
#define scheduler_h

#include <vector>
#include <string>
#include "components.h"
#include "logger.h"

void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses);
bool QueuesIsEmpty(std::vector<Queue>& queues);
#endif
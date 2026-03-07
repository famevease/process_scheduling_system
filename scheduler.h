#ifndef scheduler_h
#define scheduler_h

#include <vector>
#include <string>
#include "components.h"
#include "logger.h"

void runSimulation(std::vector<Queue>& queues, std::vector<Process>& allProcesses, Logger& logs);
bool QueuesIsEmpty(std::vector<Queue>& queues);
void loadNewProcesses(int curTime, std::vector<Queue>& queues, std::vector<Process>& Processes);

#endif
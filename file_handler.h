#ifndef file_handler_h
#define file_handler_h
#include <fstream>
#include <sstream>
#include "components.h"

void readFile(const std::string& filename, std::vector<Queue>& queues, std::vector<Process>& processes);

#endif
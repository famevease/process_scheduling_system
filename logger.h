#ifndef logger_h
#define logger_h

#include <vector>
#include <string>
#include <fstream>
#include "components.h"

struct Log
{
    int start;
    int end;
    int pid;
    int qid;
};
struct Logger
{
    std::vector<Log> Logs;
    
    void addLog(int currentTime,int pid,int qid);
};



#endif
#include "logger.h"

void Logger::addLog(int curTime, int pid, int qid){
    if (Logs.back().pid == pid)
    {
        Logs.back().end = curTime + 1;
    }
    else{
        Log temp = {curTime,curTime + 1, pid, qid};
        Logs.push_back(temp);
    }
    
}
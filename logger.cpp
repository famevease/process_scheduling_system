#include "logger.h"

void Logger::addLog(int curTime, int pid, int qid){

    if (!Logs.empty() && Logs.back().pid == pid )
    {
        Logs.back().end = curTime + 1;
    }
    else{
        Log temp = {curTime,curTime + 1, pid, qid};
        Logs.push_back(temp);
    }
}

void Logger::printOutput(){
    std::cout << "\n==== CPU SCHEDULING DIAGRAM ====" << std::endl;
    
    
    for (const auto& log : Logs) { // const de khong bi thay doi duoc
        std::cout << "[" << log.start << "-" << log.end << "] "
                  << "Q" << log.qid << " "
                  << "P" << log.pid << std::endl;
    }
}
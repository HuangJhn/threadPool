
#ifndef _MYLOG_H_
#define _MYLOG_H_

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<future>
#include<vector>
#include<memory>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

class lockLog;

class lockLog{

    public:
        static lockLog* instance();

        void printLog(std::string mess);

    private:
        lockLog();

        lockLog(const lockLog &)=delete;

        lockLog * operator=(const lockLog & ) = delete;

        void init();

        std::string getTime();
    private:
        int _fileFd;
        std::mutex _mx;
        static lockLog * _log;
};

lockLog * lockLog::_log = new lockLog();

lockLog * 
lockLog::instance(){

    return _log;
}

lockLog::lockLog():_fileFd(-1){

    init();
}

void 
lockLog::init(){

    std::string name = getTime();

    name+=".txt";

    _fileFd = open(name.c_str(),O_WRONLY | O_CREAT);

    if(_fileFd < 0){

        std::cout << "failed" << std::endl;
    }
}

std::string 
lockLog::getTime(){

    time_t now = time(0);
    return to_string(now);
}

void 
lockLog::printLog(std::string mess){

    unique_lock<mutex> lk(_mx);
    time_t now = time(0);
    std::string content = ctime(&now);
    content+="\tINFO\t"+mess + "\n\n";
    write(_fileFd,content.c_str(),content.size());
}

#define mylog lockLog::instance()

#endif//!_MYLOG_H_



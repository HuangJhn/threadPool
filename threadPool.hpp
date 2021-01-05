
#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

// author: huangJ
// time: 2020-01-05

#include<iostream>
#include<thread>
#include<functional>
#include<future>
#include<map>
#include<vector>
#include<atomic>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;

class ThreadPool{

    public:
        ThreadPool(int poolNumber);

        template<class F,class...Args>
        auto pushTasks(F && f, Args &&...args)->std::future<typename std::result_of<F(Args...)>::type>;

        ThreadPool(const ThreadPool &)=delete;
        void operator=(const ThreadPool &)=delete;
    private:
        vector<std::thread> _thdVec;
        // packaged_task<void()> packaged_task
        // function<void()> tasks;
        queue<function<void()>> _tasks;
        atomic<bool> _isStop;
        condition_variable _cond;
        mutex _m;
        
};

ThreadPool::ThreadPool(int poolNumber):_isStop(false){

    if(poolNumber < 5){

        poolNumber = 5;
    }
    for(int i = 0; i < 5; ++i){

        _thdVec.push_back(std::thread([this]{

            // std::unique_lock<std::mutex> lock(_m);
            // std::lock_guard<std::mutex> lock(_m);
            // std::scoped_lock<std::mutex> lock(_m);
            std::unique_lock<std::mutex> lock(_m);

            _cond.wait(lock,[this]{

                if(_tasks.empty() || _isStop){

                    return false;
                }
            });
            
            if(_isStop && _tasks.empty()){

                return;
            }

            auto task = std::move(_tasks.front());
            _tasks.pop();

            task();

        }));
    }
}





#endif //!_THREADPOOL_H_
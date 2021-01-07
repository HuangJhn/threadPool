
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
#include<memory>
using namespace std;

class ThreadPool{

    public:
        ThreadPool(int poolNumber);

        template<class F,class...Args>
        auto pushTasks(F && f, Args &&...args)->std::future<typename std::result_of<F(Args...)>::type>;

        ~ThreadPool();
    private:
        vector<std::thread> _thdVec;
        queue<packaged_task<void()>> _tasks;
    private:
        atomic<bool> _isStop;
        condition_variable _cond;
        mutex _m;
        
};

ThreadPool::ThreadPool(int poolNumber):_isStop(false){

    if(poolNumber < 5){

        poolNumber = 5;
    }
    for(int i = 0; i < poolNumber; ++i){

        _thdVec.push_back(std::thread([this]{

            for(;;){
                
                std::unique_lock<std::mutex> lock(_m);
                
                _cond.wait(lock,[this]{

                    if(_tasks.empty() || _isStop){

                        return false;
                    }
                    return true;
                });
                if(_isStop && _tasks.empty())   return; //结束线程
                std::cout << "executable" << std::endl;
                auto task = std::move(_tasks.front());
                _tasks.pop();
                task();
            }
        }));
    }
}

template<class F,class ... Args>
auto
ThreadPool::pushTasks(F && f,Args&&...args)->std::future<typename std::result_of<F(Args...)>::type>{

    using ret_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<ret_type()>>
    (std::bind(std::forward<F>(f),std::forward<Args>(args)...));

    future<ret_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_m);
        if(_isStop)
            return res;
        _tasks.emplace([task]{

            (*task)();
        });
    } 
    _cond.notify_all();
    return res;  
}

ThreadPool::~ThreadPool(){

    {
        std::unique_lock<std::mutex> lock(_m);
        _cond.wait(lock,[this]{

            if(_tasks.empty())  return true;
            return false;
        });
        std::cout << "kill the thread pool" << std::endl;
        _isStop = true;
    }
    for(auto & thd:_thdVec){

        thd.join();
    }
}





#endif //!_THREADPOOL_H_
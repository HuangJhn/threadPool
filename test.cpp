
#include<iostream>
#include<unistd.h>
#include"threadPool.hpp"
#include"mylog.hpp"

using namespace std;

void doTest(){


    // cout << "other thread execute it" << endl;
    mylog->printLog("other thread execute it");

}

int main(){

    ThreadPool test(5);

    test.pushTasks([]{

        // std::cout << "this content running the thread" << std::endl;
        mylog->printLog("this content running the thread");
        
    });

    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));
    test.pushTasks(std::bind(doTest));

    std::vector<std::future<void>> ftVec;

    for(int i = 0; i < 10; i++){

        // ftVec = test.pushTasks();
        ftVec.push_back(test.pushTasks(std::bind(doTest)));
    }
    std::cout << "over the threadpool" << std::endl;

    return 0;
}
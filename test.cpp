
#include<iostream>
#include<unistd.h>
#include"threadPool.hpp"

using namespace std;

void doTest(){


    cout << "other thread execute it" << endl;

}

int main(){

    ThreadPool test(5);

    test.pushTasks([]{

        std::cout << "this content running the thread" << std::endl;
        
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


    // sleep(4);make
    
    return 0;
}
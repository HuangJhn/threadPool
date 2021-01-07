
#include<iostream>
#include<unistd.h>
#include"threadPool.hpp"

using namespace std;

void doTest(){


    cout << "other thread execute it" << endl;

}

int main(){

    ThreadPool tasks(10);
    for(int i = 0; i < 10; i++){

        tasks.pushTasks(std::bind(doTest));
    }
    return 0;
}
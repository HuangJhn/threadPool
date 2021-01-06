
#include<iostream>
#include"threadPool.hpp"

using namespace std;

void doTest(){


    cout << "other thread execute it" << endl;

}

int main(){

    ThreadPool test(5);

    test.pushTasks(std::bind(doTest));

    
    return 0;
}
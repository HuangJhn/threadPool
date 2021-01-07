
#include<functional>
#include<memory>
#include<iostream>
#include<future>

using namespace std;

int doTest(){

    cout << "hello world" << endl;
    return 10;
}

template<class F, class...Args>
auto
funtionTest(F && f, Args&&...args)->std::future<typename std::result_of<F(Args...)>::type>{


}
int main(){


    function<int()> func(std::bind(doTest));

    int n = func();
    cout << n << endl;
    return 0;
}




test:clear test.cpp
	g++ -std=c++11 test.cpp -o test -lpthread

clear:
	rm -rf test
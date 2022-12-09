target:
	g++ -std=c++11 $(ws)/main.cpp && ./a.out < $(ws)/input.txt

example:
	g++ -std=c++11 $(ws)/main.cpp && ./a.out < $(ws)/example.txt

example2:
	g++ -std=c++11 $(ws)/main.cpp && ./a.out < $(ws)/example2.txt
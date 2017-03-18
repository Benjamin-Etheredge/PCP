all:
	g++ main.cpp -o main PCPProgram.cpp item.cpp -std=c++11
clean: 
	rm -f *o main

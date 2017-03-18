all:
	g++ main.cpp -o PCP PCPProgram.cpp item.cpp -std=c++11
clean: 
	rm -f *o main

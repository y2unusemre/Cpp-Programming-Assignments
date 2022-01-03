all: output


output: main.o 
		g++ main.o -o output -std=c++11


main.o: main.cpp
		g++ -c main.cpp -std=c++11


clean:	
		rm -rf *o output

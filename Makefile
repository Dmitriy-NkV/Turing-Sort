all:
	g++ -std=c++17 main.cpp src/tape.cpp src/tape_sorter.cpp -o main

clean:
	rm -rf *.o main
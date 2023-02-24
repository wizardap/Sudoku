FLAG  = -std=c++17
all:
	g++ $(FLAG) -c Sudoku.cpp
	g++ $(FLAG) -c main.cpp
	g++ $(FLAG) Sudoku.o main.o -o main
run:
	./main
clean:
	del -rf *.o main.exe
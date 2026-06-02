gen-insight:
	tail -n +1 include/*.hpp src/*.cpp main.cpp Makefile > full_project.txt

compile:
	g++ -std=c++20 main.cpp src/player.cpp src/board.cpp src/game.cpp -o main

compile-and-execute: compile
	./main

execute:
	./main
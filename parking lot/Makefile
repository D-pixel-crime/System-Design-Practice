gen-insight:
	tail -n +1 include/*.hpp src/*.cpp interfaces/*.hpp main.cpp Makefile > full_project.txt

compile:
	g++ -std=c++20 main.cpp src/*.cpp -o output

execute:
	./output

compile-execute: compile execute
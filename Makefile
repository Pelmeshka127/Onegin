all: task1

task1: main.o text_functions.o
	g++ main.o text_functions.o -o onegin

main.o: main.cpp
	g++ main.cpp -c -o main.o 

text_processing.o: text_functions.cpp 
	g++ text_functions.cpp -c -o text_functions.o s

.PHONY: clean

clean:
	rm *.o onegin








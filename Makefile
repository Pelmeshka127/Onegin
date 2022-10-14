all: sort_onegin

sort_onegin: main.o text_functions.o supporting_functions.o
	g++ main.o text_functions.o supporting_functions.o -o onegin

main.o: main.cpp
	g++ main.cpp -c -o main.o 

text_functions.o: text_functions.cpp 
	g++ text_functions.cpp -c -o text_functions.o

supporting_functions.o: supporting_functions.cpp
	g++ supporting_functions.cpp -c -o supporting_functions.o

.PHONY: clean

clean:
	rm *.o exec

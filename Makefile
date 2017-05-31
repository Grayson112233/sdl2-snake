main: main.o graphics.o inputs.o
	g++ -g -std=c++11 -o main.out main.o graphics.o inputs.o -lSDL2

main.o: main.cpp
	g++ -g -c -std=c++11 main.cpp

graphics.o: graphics/graphics.cpp
	g++ -g -c -std=c++11 graphics/graphics.cpp

inputs.o: input/inputs.cpp
	g++ -g -c -std=c++11 input/inputs.cpp

clean:
	rm *.o
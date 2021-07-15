run: p1
	./assn06
p1 : p1.o Matrix.o
	g++ -o assn06 p1.o Matrix.o
p1.o : p1.cpp
	g++ -c -g -Wall -std=c++14 -pedantic-errors -00  p1.cpp
Matrix.o: Matrix.cpp Matrix.h
	g++ -c -g -Wall -std=c++14 -pedantic-errors -00 Matrix.cpp
clean:
	rm -f *.o
	rm -f *~

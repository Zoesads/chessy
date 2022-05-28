build:
	g++ -c -Wall -O3 -Iincludes src/*.c
	g++ *.o -o Chessy
	del *.o
	
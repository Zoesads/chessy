build:
	g++ -c -O3 -Iincludes src/*.c
	g++ *.o -o Chessy
	del *.o
	
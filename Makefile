build:
	gcc -c -Wall -O3 -Iincludes src/*.c
	gcc *.o -o Chessy

clean:
	del *.o
	
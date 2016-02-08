EXEC=main

main:main.o
	gcc main.c -o main -Wall -lSDL2

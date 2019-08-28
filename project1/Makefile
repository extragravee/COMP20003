dict1: main.o bst.o
	gcc -Wall -g main.o bst.o -o dict1
	
main.o: main.c
	gcc -Wall -g main.c -o main.o 
	valgrind --leak-check=full -v ./main.o infile.csv outfile.txt < input.txt

bst.o: bst.c bst.h
	gcc -Wall -g bst.c -o bst.o 

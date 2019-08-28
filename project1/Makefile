stage1: stage1.c
	gcc -Wall -g stage1.c -o stage1
	valgrind --leak-check=full -v ./stage1 infile.csv outfile.txt < input.txt
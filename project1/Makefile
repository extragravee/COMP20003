dict1: main.o 
	gcc -Wall -g main.o -o dict1
	
main.o: main.c
	gcc -Wall -g main.c -o main.o -c

runtest:
	./dict1 infile.csv output.txt
# 	./dict1 2018sample1_no_headers.csv output.txt

runmemtest:
	valgrind --leak-check=full -v ./dict1 2018sample1_no_headers.csv output.txt



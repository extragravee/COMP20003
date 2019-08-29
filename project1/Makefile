dict1: main.o trip_logs.o 
	gcc -Wall -g main.o trip_logs.o -o dict1
	
main.o: main.c trip_logs.h 
	gcc -Wall -g main.c -o main.o -c

trip_logs.o: trip_logs.c trip_logs.h 
	gcc -Wall -g trip_logs.c -o trip_logs.o -c

# bst.o: bst.c bst.h trip_logs.h
# 	gcc -Wall -g bst.c -o bst.o -c

test:
	./dict1 infile.csv output.txt
# 	./dict1 2018sample3_no_headers.csv output.txt

memtest:
	valgrind --leak-check=full -v ./dict1 2018sample3_no_headers.csv output.txt


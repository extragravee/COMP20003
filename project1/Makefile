dict1: main.o trip_logs.o
	gcc -Wall -g main.o trip_logs.o -o dict1
	
main.o: main.c trip_logs.h
	gcc -Wall -g main.c -o main.o -c

trip_logs.o: trip_logs.c trip_logs.h
	gcc -Wall -g trip_logs.c -o trip_logs.o -c

test:
	./dict1 infile.csv output.txt
# 	./dict1 2018sample1_no_headers.csv output.txt

memtest:
# 	valgrind --leak-check=full -v ./dict1 2018sample1_no_headers.csv output.txt
	valgrind --leak-check=full -v ./dict1 infile.csv output.txt


dict1: main.o trip_logs.o bst.o duplicate_ll.o
	gcc -Wall -g bst.o main.o trip_logs.o duplicate_ll.o -o dict1
	
main.o: main.c trip_logs.h bst.h duplicate_ll.h
	gcc -Wall -g main.c -o main.o -c

trip_logs.o: trip_logs.c trip_logs.h 
	gcc -Wall -g trip_logs.c -o trip_logs.o -c

bst.o: bst.c bst.h trip_logs.h duplicate_ll.h
	gcc -Wall -g bst.c -o bst.o -c

duplicate_ll.o: duplicate_ll.c trip_logs.h duplicate_ll.h
	gcc -Wall -g duplicate_ll.c -o duplicate_ll.o -c

test:
	./dict1 2018sample1_no_headers.csv output.txt < input.txt

memtest:
	valgrind --leak-check=full -v ./dict1 2018sample1_no_headers.csv output.txt <input.txt

memtest2:
	valgrind --leak-check=full -v ./dict1 2018sample2_no_headers.csv output.txt <input.txt

memtest3:
	valgrind --leak-check=full -v ./dict1 2018sample3_no_headers.csv output.txt <input.txt

# dup_test:
# 	make dict1
# 	./dict1 2018sample1_no_headers.csv > output.txt
# 	grep duplicate: output.txt
	

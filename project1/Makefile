dict1: main.o trip_logs.o bst.o duplicate_ll.o 
	gcc -Wall -g bst.o main.o trip_logs.o duplicate_ll.o -o dict1

dict2: main2.o bst.o trip_logs.o duplicate_ll.o
	gcc -Wall -g bst.o main2.o trip_logs.o duplicate_ll.o -o dict2
	
main.o: main.c bst.h 
	gcc -Wall -g main.c -o main.o -c

trip_logs.o: trip_logs.c trip_logs.h 
	gcc -Wall -g trip_logs.c -o trip_logs.o -c

bst.o: bst.c bst.h trip_logs.h duplicate_ll.h
	gcc -Wall -g bst.c -o bst.o -c

duplicate_ll.o: duplicate_ll.c trip_logs.h duplicate_ll.h
	gcc -Wall -g duplicate_ll.c -o duplicate_ll.o -c

main2.o: main2.c bst.h 
	gcc -Wall -g main2.c -o main2.o -c


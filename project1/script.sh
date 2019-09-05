#!/bin/bash

for i in {100..100000..100}
do
	shuf -n $i 2018full_size_no_headers\ \(1\).csv > current.txt
	shuf -n 100 current.txt | awk -F ',' '{print $16}' > input.txt
	echo "$i------"
	printf "$i," >> stats.csv
	./dict1 current.txt output.txt < input.txt | awk -F ' --> ' '{sum+=$2} END {print sum/100}' >>stats.csv
done


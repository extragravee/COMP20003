#!/bin/bash

shuf -n 100 2018sample2_no_headers.csv | awk -F ',' '{print $16}' > input.txt
./dict1 2018sample2_no_headers.csv  output.txt < input.txt | awk -F ' --> ' '{sum+=$2} END {print sum/100}'

#!/bin/bash

# Tom Nguyen                                                                                                  
# October 20, 2017                                                                                            
# CSE 374
# Homework 3: Part 3


if [ $# -lt 2 ]
then
    echo "$0: needs at least 2 arguments: input output"
    exit 1
elif [ ! -e "$1" ]
then
    echo "$0: $1 does not exist"
    exit 1
fi

count=1

while read line                     # processes the file provided in arg #1 line-by-line
do
    echo "Performing measurement on $line..."
    result=$(./perform-measurement.sh "$line")
    if [ $result -ne '0' ]
    then
	echo "$count $line $result" >> "$2"
	echo "...success"
    else
	echo "...failed"
    fi
    ((count++))
done < "$1"

exit 0

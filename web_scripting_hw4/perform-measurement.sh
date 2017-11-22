#!/bin/bash

# Tom Nguyen                                                                                                  
# October 20, 2017                                                                                            
# CSE 374
# Homework 3: Part 1  


if [ $# -lt 1 ]
then
    echo "$0: needs one or more arguments: f1 f2 ..."
    exit 1
fi

file=$(mktemp)
wget -O "$file" -T 10 --tries=3 "$1" &> /dev/null

if [ $?	-ne 0 ]                        # if the wget was sucesseful
then
    echo "0"
else 
    wc -c < "$file"
fi

rm "$file"                             # deletes temp file

exit 0

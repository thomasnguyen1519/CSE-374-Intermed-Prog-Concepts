#!/bin/bash

# Tom Nguyen                                                                                                  
# October 20, 2017                                                                                            
# CSE 374                                                                                                     
# Homework 3: Part 2



if [ $# -lt 2 ]
then
    echo "$0: needs two arguments: index.html output"
    exit 1
elif [ ! -e "$1" ]
then
    echo "$0: $1 does not exist"
    exit 1
fi


grep 'http' "$1" | sed -e 's/.*http:\/\//http:\/\//' | sed 's/\(http:\/\/[a-z0-9\.-]*\/\).*/\1/' | sed -E 's/^http:\/\/((babelfish)|(www\.100bestwebsites)|(en\.wiki)).*//g' | egrep '^[a-z]+' > "$2"

exit 0

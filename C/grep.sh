#!/bin/bash

# Check if the correct number of arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: ./grep.sh <regex> <line>"
    exit 1
fi

# Assign the arguments to variables
regex=$1
line=$2

# Build the project quietly, discarding the output
cmake --build build > /dev/null 2>&1

# Run the 'grep' executable with the provided arguments
./src/grep "${regex}" "${line}"

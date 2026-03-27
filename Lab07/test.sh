#!/bin/bash

read -p "Which task: " task

./compile.sh

if [[ "$task" -eq 1 ]]; then
	./Lab0701_EthanLuh.out
	cat alphabet.txt
elif [[ "$task" -eq 2 ]]; then
        ./Lab0702_EthanLuh.out
	cat hello.txt
elif [[ "$task" -eq 3 ]]; then
        ./Lab0703_EthanLuh.out
else
	echo 'No tasks'
fi
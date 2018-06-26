#!/bin/bash

for((i=1;i<=1000;i++))
do
	./build/extctl
	echo ">>> $i <<<"
	sleep 1
done


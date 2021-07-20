#!/usr/bin/env bash

# File: eval.sh
# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Script for running Evolution algorithm 100 times
# Details: Scritp finds name of used grammar(filename),
# 		   uses output/ its name as output folder.
#		   If output folder does not exist, creates one.
# Version: 0.1
# Copyright (c) 2021

# FNV hash 64 const 0xCBF29CE484222325 - can be used as magic number

#use input arguments as array
array=("$@")
arrLength=${#array[@]}

#find if -o argument is in input array
for (( i = 0; i < ${arrLength}; i++)); do
	if [[ ${array[$i]} == "-o" ]]; then
		echo "Error: Output argument found." 1>&2
		exit 1
	fi
done


#in argument array find name of input file
for (( i = 0; i < ${arrLength}; i++)); do
	if [[ ${array[$i]} == "-i" ]]; then
		input="${array[$i+1]##*/}"
	fi
done

#set ouput path for given grammar
output="output/$input"

#if parameters are given execute 30 runs of evolution
if [[ $# -gt 0 ]]; then

	#if output/gramar folder does not exist, create one
	if [[ ! -d "$output" ]]; then
		mkdir -p "$output"
	fi

	#run Evolution 30 times
	for ((i = 0; i < 30; i++)); do
		./build/src/GEHash "$@" "-o ${output}/output${i}.json"
	done
fi
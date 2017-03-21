#!/bin/sh

cd ../

printf "cat < newOutputFile1 " |  bin/rshell #(view original contents)

printf "cat < existingInputFile | tr A-Z a-z > newOutputFile1" |  bin/rshell #(convert upper to lower & output)

printf "cat < newOutputFile1 " |  bin/rshell #(view new contents)

printf "cat < existingInputFile | tr A-Z a-z >> newOutputFile1" |  bin/rshell #(convert upper to lower & output w/o overwrite)

printf "cat < newOutputFile1 " |  bin/rshell #(view new contents)

printf "cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2" |  bin/rshell

printf "ls -a | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2" |  bin/rshell

printf "cat < newOutputFile1 " |  bin/rshell #(view new contents)

printf "cat < newOutputFile2 " |  bin/rshell #(view new contents)

printf "ls -a | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z >> newOutputFile2" |  bin/rshell

printf "cat < newOutputFile1 " |  bin/rshell #(view new contents)

printf "cat < newOutputFile2 " |  bin/rshell #(view new contents)
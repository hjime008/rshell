#!/bin/sh

cd ../

printf "echo hello" |  bin/rshell

printf "echo hello worls" |  bin/rshell

printf "ls -a" |  bin/rshell

printf "ls -l" |  bin/rshell

printf "ls -a -l" |  bin/rshell

printf "touch testfile1.txt testfile2.txt" |  bin/rshell

printf "cat testfile1.txt" |  bin/rshell


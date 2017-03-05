#!/bin/sh

cd ../

printf "exit" |  bin/rshell

printf "test -e tests/testfiles/document.txt || exit" |  bin/rshell

printf "test -e tests/testfiles/document.txt && exit" |  bin/rshell

printf "test -e tests/testfiles/document.txt ; exit" |  bin/rshell

printf "test -e tests/testfiles/document.txt #exit" |  bin/rshell

printf "echo (Extra prompt after or and comment symbol test shows exit was not reached, meaning test was successful.); exit" |  bin/rshell


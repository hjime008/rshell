#!/bin/sh

cd ../

printf "exit" |  bin/rshell

printf "echo Exit test with or connector || exit" |  bin/rshell

printf "echo Exit test with and connector && exit" |  bin/rshell

printf "echo Exit test with semicolon connector ; exit" |  bin/rshell

printf "echo Exit test with comment symbol #exit" |  bin/rshell

printf "echo (Extra prompt after or and comment symbol test shows exit was not reached, meaning test was successful.); exit" |  bin/rshell


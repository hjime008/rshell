#!/bin/sh

cd ../

printf "&& || ; || ; ; || || ; " |  bin/rshell

printf "&& touch README.md && exit" |  bin/rshell

printf "echo a; echo b && echo c || echo d && echo e" |  bin/rshell

printf "ls -a; echo hello world && echo world hello && echo world || echo hello; exit" |  bin/rshell

#!/bin/sh

cd ../

printf "#test1failed" |  bin/rshell

printf "test -e tests/testfiles/document.txt #test 2 failed" |  bin/rshell

printf "test -e tests/testfiles/document.txt ; #test 3 failed" |  bin/rshell

printf "test -e tests/testfiles/document.txt || echo comment test 4 pt2 ; #test 4 failed" |  bin/rshell

printf "echo comment test 5 pt1 && test -e tests/testfiles/document.txt ; #test 5 failed" |  bin/rshell

printf "echo comment test 6 pt1 #test 6 failed || test -e tests/testfiles/document.txt ; #test 6 failed" |  bin/rshell

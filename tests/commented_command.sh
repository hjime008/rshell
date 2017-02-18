#!/bin/sh

cd ../

printf "#test1failed" |  bin/rshell

printf "echo comment test 2 #test 2 failed" |  bin/rshell

printf "echo comment test 3 ; #test 3 failed" |  bin/rshell

printf "echo comment test 4 pt1 || echo comment test 4 pt2 ; #test 4 failed" |  bin/rshell

printf "echo comment test 5 pt1 && echo comment test 5 pt2 ; #test 5 failed" |  bin/rshell

printf "echo comment test 6 pt1 #test 6 failed || echo comment test 6 pt2 ; #test 6 failed" |  bin/rshell

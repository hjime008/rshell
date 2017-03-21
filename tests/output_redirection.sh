#!/bin/sh

cd ../

printf "cat < test1 " |  bin/rshell #(view original contents)

printf "cat < test2 " |  bin/rshell #(view original contents)

printf "test2 > test1 " |  bin/rshell #(output test1 to test 2)

printf "cat < test1 " |  bin/rshell #(view new contents)

printf "cat < test2 " |  bin/rshell #(view new contents)

printf "cat < test2 " |  bin/rshell #(view original contents)

printf "test3 > test2 " |  bin/rshell #(output test2 to test 3)

printf "cat < test3 " |  bin/rshell #(view new contents)

printf "test3 >> test2 " |  bin/rshell #(output test2 to test 3, no-overwrite)

printf "cat < test3 " |  bin/rshell #(view new contents)

printf "ls -a > test3" |  bin/rshell #(output command output to test3)

printf "cat < test3 " |  bin/rshell #(view new contents)

printf "ls -a >> test3" |  bin/rshell #(output command output to test3, no overwrite)

printf "cat < test3 " |  bin/rshell #(view new contents)



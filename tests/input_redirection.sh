#!/bin/sh

cd ../

printf "cat < test1 " |  bin/rshell #(view original contents)

printf "cat < test2 " |  bin/rshell #(view original contents)

printf "test2 < test1 " |  bin/rshell #(input test1 to test 2)

printf "cat < test1 " |  bin/rshell #(view new contents)

printf "cat < test2 " |  bin/rshell #(view new contents)

printf "cat < test2 " |  bin/rshell #(view original contents)

printf "test3 < test2 " |  bin/rshell #(input test2 to test 3)

printf "cat < test3 " |  bin/rshell #(view new contents)




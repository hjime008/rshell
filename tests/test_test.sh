#!/bin/sh

cd ../

printf "test -e tests/testfiles/document.txt" |  bin/rshell #normal test -e on existing file, correct result is true

printf "test -e tests/testfiles/fakedoc.txt" |  bin/rshell #normal test -e on nonexisting doc, correct result is false

printf "test -e tests/testfiles/regfile" |  bin/rshell #normal test -e on existing normal file, correct result is true

printf "test -e tests/testfiles/testdirectory" |  bin/rshell #normal test -e on existing directory, correct result is true

printf "test tests/testfiles/document.txt" |  bin/rshell #test default -e on existing doc, correct result is true

printf "test tests/testfiles/fakedoc.txt" |  bin/rshell #test default -e on nonexisting doc, correct result is false

printf "[ -e tests/testfiles/document.txt ]" |  bin/rshell #symbolic test -e on existing doc, correct result is true

printf "[ -e tests/testfiles/fakedoc.txt ]" |  bin/rshell #symbolic test -e on existing doc, correct result is false

printf "[ -f tests/testfiles/regfile ]" |  bin/rshell

printf "[ -f tests/testfiles/document.txt ]" |  bin/rshell

printf "[ -f tests/testfiles/fakedoc.txt ]" |  bin/rshell

printf "[ -d tests/testfiles/document.txt ]" |  bin/rshell

printf "[ -d tests/testfiles/fakedoc.txt ]" |  bin/rshell

printf "[ -d tests/testfiles/ ]" |  bin/rshell

printf "[ -d tests/testfiles/testdirectory ]" |  bin/rshell

printf "[ tests/testfiles/document.txt ]" |  bin/rshell

printf "[ tests/testfiles/fakedoc.txt ]" |  bin/rshell #symoblic tes


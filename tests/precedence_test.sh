printf "(echo A && echo B) || (echo C && test -e tests/testfiles/document.txt)" |  bin/rshell

printf "(echo A && echo B) || (test -e tests/testfiles/document.txt && echo D)" |  bin/rshell

printf "(echo A && test -e tests/testfiles/document.txt) || (echo C && echo D)" |  bin/rshell

printf "(test -e tests/testfiles/document.txt && echo B) || (echo C && echo D)" |  bin/rshell

printf "(echo date: && date) || (echo time: && time); echo done" |  bin/rshell 

printf "(((echo first) || (echo second && echo third); (echo fourth; echo fifth)) && echo sixth || echo seventh)" |  bin/rshell

printf "(((echo first) || (echo second && echo third); (echo fourth; echo fifth)) && echo sixth || echo seventh)" |  bin/rshell
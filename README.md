Assignment 2 "rshell"

//--------------------------------------------------------------------------------------------------
A basic shell terminal created in C++. This shell is able to run commands passed to executables stored in /bin similar to a native linux shell.
//--------------------------------------------------------------------------------------------------

-Known program bugs:

1) Extra newline printed to console following command execution
Bug status: Fixed 02/17/2017

2) When using input redirection on the rshell executable, after the last command is run, the "rshell" outputs a addtional prompt with a newline.
ex. "/bin/rshell<input.txt" will cause this  behavior.
NOTE: Problems do not appear when commands are manually input by a user.
Bug status: unresolved

3) When an && or an "||" connector is to the left or right of the command "ls" on a line, "rshell" outputs an error upon hitting that command. Other commands on the line will execute appropriately however.
Bug status: unresolved

4) If a connector is the last character input on a line, a segmentation fault will occur.
Bug status: Fixed 02/17/2017

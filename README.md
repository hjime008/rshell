Assignment 2 "rshell"

//--------------------------------------------------------------------------------------------------
A basic shell terminal created in C++. This shell is able to run commands passed to executables stored in /bin similar to a native linux shell.
//--------------------------------------------------------------------------------------------------

-Known program bugs:

1) Extra newline printed to console following command execution
Bug status: Fixed 02/17/2017

2) If the only command passed to the "rshell" exectuable indirectly trough a script is the exit command, a newline will not be output, causing the shell terminal to continue to output on the same line.
Bug status: unresolved

2) When an && or an "||" connector is to the left or right of the command "ls" on a line, "rshell" outputs an error upon hitting that command. Other commands on the line will execute appropriately however.
Bug status: unresolved

3) If a connector is the last character input on a line, a segmentation fault will occur.
Bug status: Fixed 02/17/2017

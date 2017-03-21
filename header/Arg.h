#ifndef ARG_H
#define ARG_H

#include "Single.h"
#include "Connectors.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Semicolon.h"

#include <iostream>
#include <string.h>

#include  <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

// leaf node
class Arg : public Base
{
    //Arg will have the argument string to execute
    protected:
    string data;
    
    public:
    Arg(string data) : Base(), data(data) {}
    
    //parse the string data in order to call execute on it
    //this gets rid of spaces and seperates the command from the arguments
    void final_parse(char *line, char **argv);
    
    void redirection();

    //executes the command
    void execute();
    
    void pipe_execute();
    
    void test();
    
    //this purpose of this function is to seperate the entire
    //string by the connectors in order to isolate the commands and 
    //arguments
    void parse();
    
    //this function will recursivly call itself too delete all the pointers
    //of each child node and their children
    void delete_tree(Base* node);
    
};

#endif
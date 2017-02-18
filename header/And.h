#ifndef AND_H
#define AND_H

#include "../header/Connectors.h"

//inherits from composite class
class And : public Connectors
{
    public:
    // constructor uses composite constructor
    And(Base* left, Base* right) : Connectors(left, right) {}
    
    // this function will execute the left and right child if the left child 
    // was executed
    void execute();
    
    
    //this purpose of this function is to seperate the entire
    //string by the connectors in order to isolate the commands and 
    //arguments
    void parse();
    
    //this function will recursivly call itself too delete all the pointers
    //of each child node and their children
    void delete_tree(Base* node);

};

#endif
#ifndef OR_H
#define OR_H
#include "../header/Connectors.h"

//inherits from composite class
class Or : public Connectors
{
    public:
    // constructor uses composite constructor
    Or(Base* left, Base* right) : Connectors(left, right) {}
    
    // this function will execute the left or right child if the left child 
    // was not executed
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
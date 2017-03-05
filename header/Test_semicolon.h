#ifndef TEST_SEMICOLON_H
#define TEST_SEMICOLON_H

#include "../header/Connectors.h"

//inherits from composite class
class Test_semicolon : public Connectors
{
    public:
    // constructor uses composite constructor
    Test_semicolon(Base* left, Base* right) : Connectors(left, right) {}
    
    // this function will execute the left and right child
    void execute();
    
    // this function is used to execute the test command. this test to see if the 
    // arguments will pass or fail then return that value;
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
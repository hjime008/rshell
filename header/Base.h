#ifndef BASE_H
#define BASE_H

//base class
class Base 
{
    public:
    Base* parent;
    Base* left_child;
    Base* right_child;
    bool executed;
    
    // constructor for base
    Base();
    
    //deconstructor
    virtual ~Base();
    
    
    // pure virtual fucntion implemented in the subclasses to execute 
    // the commands
    virtual void execute() = 0;
    
    //function used to split the string of commands into parts so we can
    //execute.
    virtual void parse() = 0;
    
    //this function will recursivly call itself too delete all the pointers
    //of each child node and their children
    virtual void delete_tree(Base* node) = 0;
};

#endif
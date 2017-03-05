#ifndef CONNECTORS_H
#define CONNECTORS_H

//composite class
class Connectors : public Base 
{
    public:
    // constructor for class in order to make the children
    Connectors(Base* left, Base* right);
    
    //deconstructor
    virtual ~Connectors();
    
    // pure virtual fucntion implemented in the subclasses to execute 
    // the commands
    virtual void execute() = 0;
    
    
    virtual void test() = 0;
    
    
    //this purpose of this function is to seperate the entire
    //string by the connectors in order to isolate the commands and 
    //arguments
    virtual void parse() = 0;
    
    
    //this function will recursivly call itself too delete all the pointers
    //of each child node and their children
    virtual void delete_tree(Base* node) = 0;
};

#endif
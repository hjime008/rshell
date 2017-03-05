#ifndef SINGLE_H
#define SINGLE_H

//single execute
class Single : public Base
{

    public:
    Single(Base* child);
    
    
    //will execute its single child
    void execute();
    
    
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
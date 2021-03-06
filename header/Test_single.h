#ifndef TEST_SINGLE_H
#define TEST_SINGLE_H

//single execute
class Test_single : public Base
{

    public:
    Test_single(Base* child);
    
    
    //will execute its single child
    void execute();
    
    void pipe_execute();
    
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
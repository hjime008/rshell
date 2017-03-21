#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Test_and.h"


// this function will execute the left Test_and right child if the left child 
// was executed
void Test_and::execute()
{
    test();
}

void Test_and::pipe_execute()
{
    //do nothing
}

// this function is used to execute the test command. this test to see if the 
// arguments will pass or fail then return that value;
void Test_and::test()
{
    left_child->test();
    
    
    if (left_child->executed == true)
    {
        right_child->execute();
        this->executed = true;
    }
}

//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands Test_and 
//arguments
void Test_and::parse()
{
    left_child->parse();
    right_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node Test_and their children
void Test_and::delete_tree(Base* node)
{
    if (node->left_child != 0)
    {
        delete_tree(node->left_child);
        node->left_child = 0;
    }
    if (node->right_child != 0)
    {
        delete_tree(node->right_child);
        node->right_child = 0;
    }
    
    delete node;
}
#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Test_or.h"


// this function will execute the left or right child if the left child 
// was not executed
void Test_or::execute()
{
    test();
}

// this function is used to execute the test command. this test to see if the 
// arguments will pass or fail then return that value;
void Test_or::test()
{
    left_child->test();
    
    if (left_child->executed == false)
    {
        right_child->execute();
        if (right_child->executed == true)
        {
            this->executed = true;
        }
    }
    else
    {
        this->executed = true;
    }
}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Test_or::parse()
{
    left_child->parse();
    right_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Test_or::delete_tree(Base* node)
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
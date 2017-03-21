#include "../header/Base.h"
#include "../header/Test_single.h"

Test_single::Test_single(Base* child) : Base()
{
    this->left_child = child;
    this->left_child->parent = this;
}


//will execute its Test_single child
void Test_single::execute()
{
    test();
}

void Test_single::pipe_execute()
{
    //do nothing
}

// this function is used to execute the test command. this test to see if the 
// arguments will pass or fail then return that value;
void Test_single::test()
{
    left_child->test();
    if (left_child->executed == true)
    {
        this->executed = true;
    }
}

//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Test_single::parse()
{
     left_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Test_single::delete_tree(Base* node)
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
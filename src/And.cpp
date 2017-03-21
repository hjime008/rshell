#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/And.h"


// this function will execute the left and right child if the left child 
// was executed
void And::execute()
{
    left_child->execute();
        
    if (left_child->executed == true)
    {
        right_child->execute(); //if left executed
        this->executed = true;
    }
}


void And::pipe_execute()
{
    //do nothing
}

// this connector type will not make use of the test function.
// it is only used by Test_and Test_or Test_semicolon Test_single
void And::test()
{
    
}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void And::parse()
{
    left_child->parse();
    right_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void And::delete_tree(Base* node)
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
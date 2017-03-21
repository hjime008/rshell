#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Pipe.h"
// this function will execute the left and right child
void Pipe::execute()
{
    pipe_execute();
}


void Pipe::pipe_execute()
{
    left_child->pipe_execute();
    right_child->pipe_execute();
    
    if (left_child->executed == true || right_child->executed == true)
    {
        this->executed = true;
    }
}

//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Pipe::parse()
{
    left_child->parse();
    right_child->parse();
}

// this connector type will not make use of the test function.
// it is only used by Test_and Test_or Test_semicolon Test_single
void Pipe::test()
{
    // do nothing
}

//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Pipe::delete_tree(Base* node)
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
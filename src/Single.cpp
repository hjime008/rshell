#include "../header/Base.h"
#include "../header/Single.h"

Single::Single(Base* child) : Base()
{
    this->left_child = child;
    this->left_child->parent = this;
}


//will execute its single child
void Single::execute()
{
    left_child->execute();
    if (left_child->executed == true)
    {
        this->executed = true;
    }
}

void Single::pipe_execute()
{
    //do nothing
}

void Single::test()
{
    
}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Single::parse()
{
     left_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Single::delete_tree(Base* node)
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
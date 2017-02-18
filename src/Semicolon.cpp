#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Semicolon.h"

// this function will execute the left and right child
void Semicolon::execute()
{
    left_child->execute();
    right_child->execute();
    
    if (left_child->executed == true || right_child->executed == true)
    {
        this->executed = true;
    }
}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Semicolon::parse()
{
    left_child->parse();
    right_child->parse();
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Semicolon::delete_tree(Base* node)
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
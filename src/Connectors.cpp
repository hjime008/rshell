#include "../header/Base.h"
#include "../header/Connectors.h"

Connectors::Connectors(Base* left, Base* right) : Base()
{
    this->left_child = left;
    this->left_child->parent = this;
    this->right_child = right;
    this->right_child->parent = this;
}

Connectors::~Connectors()
{
    
}
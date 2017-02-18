#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Single.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Semicolon.h"
#include "../header/Arg.h"

#include <iostream>
#include <string.h>

#include  <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

//parse the string data in order to call execute on it
//this gets rid of spaces and seperates the command from the arguments
void Arg::final_parse(char *line, char **argv)
{
    while (*line != '\0') /* if not the end of line ....... */ 
    { 
        while (*line == ' ' || *line == '\t' || *line == '\n')
        {
            *line++ = '\0';     /* replace white spaces with 0    */
        }
        
        *argv++ = line;          /* save the argument position     */
        
        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
        {
            line++;             /* skip the argument until ...    */
        }
    }
    
    *argv = '\0';                 /* mark the end of argument list  */
}


//executes the command
void Arg::execute()
{
    if (data == " ")
    {
        return;
    }
    
    char  line[1024];             /* the input line                 */
    strcpy(line, data.c_str());
    char  *argv[64];              /* the command line argument      */
    
    final_parse(line, argv);
    
    if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
        exit(0);            /*   exit if it is                */
           
    pid_t  pid;
    int    status;

    if ((pid = fork()) < 0)  /* fork a child process           */
    {    
        perror("Error: fork child failed\n");
        exit(1);
    }
    else if (pid == 0) /* for the child process:         */
    {          
        if (execvp(*argv, argv) < 0) /* execute the command  */
        {     
            perror("Error: execution failed\n");
            exit(1);
        }
    }
    else /* for the parent:      */
    {                                  
        while (wait(&status) != pid)/* wait for completion  */
        {
            //do nothing
        }
        
        this->executed = true;
    }

}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Arg::parse()
{
    unsigned position = 0;
    Base* temp = 0;
    
    //seperate the string by comment
    if (data.find("#") != string::npos)
    {
        string left_side;
        
        position = data.find("#");       
        if (position == 0)
        {
            left_side = " ";
        }
        else
        {
            left_side = data.substr(0, position);
        }
        
        //found the character then seperated into two strings then make a new 
        //node based on if we are working with the right or left child
        if (parent->left_child == this)
        {
            temp = parent->left_child;
            parent->left_child = new Single(new Arg(left_side));
            parent->left_child->parent = temp->parent;
            
            parent->left_child->left_child->parse();
        }
        else
        {
            temp = parent->right_child;
            parent->right_child = new Single(new Arg(left_side));
            parent->right_child->parent = temp->parent;
            
            parent->right_child->left_child->parse();
        }
        
        delete temp;
    }
    //seperate the string by a semicolon
    else if (data.find(";") != string::npos)
    {
        string left_side;
        string right_side;
        
        position = data.find(";");
        if (position == 0 && position == data.size() - 1)
        {
            left_side = " ";
            right_side = " ";
        }
        else if (position == 0)
        {
            left_side = " ";
            right_side = data.substr((position + 1));
        }
        else if (position == data.size() - 1)
        {
            left_side = data.substr(0, position);
            right_side = " ";
        }
        else 
        {
            left_side = data.substr(0, position);
            right_side = data.substr((position + 1));   
        }
        
        
        
        //found the character then seperated into two strings then make a new 
        //node based on if we are working with the right or left child
        if (parent->left_child == this)
        {
            temp = parent->left_child;
            parent->left_child = new Semicolon(new Arg(left_side), new Arg(right_side));
            parent->left_child->parent = temp->parent;
            
            parent->left_child->left_child->parse();
            parent->left_child->right_child->parse();
        }
        else
        {
            temp = parent->right_child;
            parent->right_child = new Semicolon(new Arg(left_side), new Arg(right_side));
            parent->right_child->parent = temp->parent;
            
            parent->right_child->left_child->parse();
            parent->right_child->right_child->parse();
        }
        
        delete temp;
        
    }
    //seperate by a &&
    else if (data.find("&&") != string::npos)
    {
        
        string left_side;
        string right_side;
        
        position = data.find("&&");
        if (position == 0 && position == data.size() - 2)
        {
            left_side = " ";
            right_side = " ";
        }
        else if (position == 0)
        {
            left_side = " ";
            right_side = data.substr((position + 2));
        }
        else if (position == data.size() - 2)
        {
            left_side = data.substr(0, position);
            right_side = " ";
        }
        else
        {
            left_side = data.substr(0, position);
            right_side = data.substr((position + 2));
        }
        
        
        //found the character then seperated into two strings then make a new 
        //node based on if we are working with the right or left child
        if (parent->left_child == this)
        {
            temp = parent->left_child;
            parent->left_child = new And(new Arg(left_side), new Arg(right_side));
            parent->left_child->parent = temp->parent;
            
            parent->left_child->left_child->parse();
            parent->left_child->right_child->parse();
        }
        else
        {
            temp = parent->right_child;
            parent->right_child = new And(new Arg(left_side), new Arg(right_side));
            parent->right_child->parent = temp->parent;
            
            parent->right_child->left_child->parse();
            parent->right_child->right_child->parse();
        }
        
        delete temp;
        
    }
    //seperate by a ||
    else if (data.find("||") != string::npos)
    {
        string left_side;
        string right_side;
        
        position = data.find("||");
        if (position == 0 && position == data.size() - 2)
        {
            left_side = " ";
            right_side = " ";
        }
        else if (position == 0)
        {
            left_side = " ";
            right_side = data.substr((position + 2));
        }
        else if (position == data.size() - 2)
        {
            left_side = data.substr(0, position);
            right_side = " ";
        }
        else
        {
            left_side = data.substr(0, position);
            right_side = data.substr((position + 2));
        }
        
        
        //found the character then seperated into two strings then make a new 
        //node based on if we are working with the right or left child
        if (parent->left_child == this)
        {
            temp = parent->left_child;
            parent->left_child = new Or(new Arg(left_side), new Arg(right_side));
            parent->left_child->parent = temp->parent;
            
            parent->left_child->left_child->parse();
            parent->left_child->right_child->parse();
        }
        else
        {
            temp = parent->right_child;
            parent->right_child = new Or(new Arg(left_side), new Arg(right_side));
            parent->right_child->parent = temp->parent;
            
            parent->right_child->left_child->parse();
            parent->right_child->right_child->parse();
        }
        
        delete temp;
        
    }
    else
    {
        //do nothing
    }
}


//this function will recursivly call itself too delete all the pointers
//of each child node and their children
void Arg::delete_tree(Base* node)
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
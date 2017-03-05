#include "../header/Base.h"
#include "../header/Connectors.h"
#include "../header/Single.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Semicolon.h"
#include "../header/Test_single.h"
#include "../header/Test_and.h"
#include "../header/Test_or.h"
#include "../header/Test_semicolon.h"
#include "../header/Arg.h"

#include <iostream>
#include <string.h>
#include <stack>
#include <vector>
#include <algorithm>

#include  <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
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


//this fucntion uses the string inside the variable data to 
//see whether the argument will pass of fail and returns the bool
void Arg::test()
{
   string rawString = data;
   string directory;
  
  //cout << "Incoming string: " << rawString << endl;
  int flagLocation = rawString.find("-");
  int dirStart = 0;
  int dirEnd = 0;
  

  if(rawString.find("-") == string::npos)
  {
     dirStart = rawString.find_first_not_of(" []"); //compensating for location of first char
     dirEnd = (rawString.find_last_not_of(" []") + 1); //compensating for location of last char
     
     directory = rawString.substr(dirStart, (dirEnd - dirStart));
     //cout << directory << endl;
     
     struct stat s1;
        if(stat(directory.c_str(), &s1) != 0)
        {
           //cerr<<"Input does not exist. (-e)" << endl;
           cout << "(False)" << endl;
           return;
        }
        else
        {
           cout << "(True)" << endl;
           executed = true;
           return;
        }
  }
  else
  {
     dirStart = rawString.find_first_not_of("/", flagLocation + 3);
     char spaceChar = ' ';
    
     if(rawString.at( flagLocation + 2 ) != spaceChar)//check that flag is single char
     {
        //cout << "error: incorrect flag" << endl;
        //perror("Error: unrecognized flag\n");
        cout << "(False)" << endl;
        return;
     }
     
     dirEnd = (rawString.find_last_not_of(" []") + 1); //compensating for location of last char
     directory = rawString.substr(dirStart, (dirEnd - dirStart));
          
     char flagChar = rawString.at(flagLocation + 1);
     char flagCharE = 'e';
     char flagCharF = 'f';
     char flagCharD = 'd';
     
      //cout << directory << endl;
      //cout << flagChar << endl;
     
     if(flagChar == flagCharE)
     {
        struct stat s1;
        if(stat(directory.c_str(), &s1) != 0)
        {
           //cerr<<"Input does not exist. (-e)" << endl;
           cout << "(False)" << endl;
           return;
        }
        else
        {
           cout << "(True)" << endl;
           executed = true;
           return;
        }
     }
     else if(flagChar == flagCharF)
     {
        struct stat s1;
        if(stat(directory.c_str(), &s1) != 0)
        {
           //cerr<<"Input does not exist. (-f)" << endl;
           cout << "(False)" << endl;
           return;
        }
        else if(!(s1.st_mode & S_IFREG))
        {
	        //cerr<<"Input is not a regular file. (-f)" << endl;
	        cout << "(False)" << endl;
	        return;
        }
        else
        {
           cout << "(True)" << endl;
           executed = true;
           return;
        }
     }
     else if(flagChar == flagCharD)
     {
        struct stat s1;
        if( stat(directory.c_str(), &s1) != 0)
        {
           //cerr<<"Input does not exist. (-d)" << endl;
           cout << "(False)" << endl;
           return;
        }
        else if(!(s1.st_mode & S_IFDIR))
        {
	        //cerr<<"Input is not a directory. (-d)" << endl;
	        cout << "(False)" << endl;
	        return;
        }
        else
        {
           cout << "(True)" << endl;
           executed = true;
           return;
        }
     }
     else
     {
        //cout << "error: enter different flag (-e, -f, or -d)" << endl;
        //perror("Error: unrecognized flag\n");
        cout << "(False)" << endl;
     }
     
     
  }
}


//this purpose of this function is to seperate the entire
//string by the connectors in order to isolate the commands and 
//arguments
void Arg::parse()
{
    unsigned position = 0;
    unsigned bracket_pos = 0;
    Base* temp = 0;
    
    if(data.size() == 0)
    {
        return;
    }
    
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
    // **IMPORTANT** START OF PARETHESIS CHECK
    else if (data.at(0) == '(')
    {
        string left_side;
        string right_side;
        
    
        
        unsigned curr_pos = 0;
        vector<int> paren_pos;
        
        while (data.find("(", curr_pos) != string::npos)
        {
            curr_pos = data.find("(", curr_pos);
            paren_pos.push_back(curr_pos);
            curr_pos += 1;
            
        }
        
        curr_pos = 0;
        
        while (data.find(")", curr_pos) != string::npos)
        {
            curr_pos = data.find(")", curr_pos);
            paren_pos.push_back(curr_pos);
            curr_pos += 1;
            
        }
        
        if (paren_pos.size() % 2 == 0)
        {
            
            //unsigned min_index = 0;
            // for (unsigned i = 0; i < paren_pos.size(); ++i)
            // {
            //     min_index = i;
            //     for (unsigned j = 0; j < paren_pos.size(); ++j)
            //     {
            //         if (paren_pos.at(j) < paren_pos.at(min_index))
            //         {
            //             min_index = j;
            //         }
            //     }
            
            //     swap(paren_pos.at(i), paren_pos.at(min_index));
            // }
            
            sort(paren_pos.begin(), paren_pos.end());
            
            
            
            if (data.at(paren_pos.at(0) == '('))
            {
                stack<int> find_position;
                find_position.push(paren_pos.at(0));
                
                // finds the position for the pair of parenthesis
                for (unsigned i = 1; i < paren_pos.size(); ++i)
                {
                    if (data.at(paren_pos.at(i)) == '(')
                    {
                        find_position.push(paren_pos.at(i));
                    }
                    else
                    {
                        find_position.push(paren_pos.at(i));
                        bracket_pos = find_position.top();
                        find_position.pop();
                        find_position.pop();
                        
                        if (find_position.empty())
                        {
                            break;
                        }
                    }
                }

            }
            else
            {
                perror("Error: syntax error with parenthesis\n");
                exit(1);
            }
            
            
            
        }
        else
        {
            perror("Error: not even pair of parenthesis\n");
            exit(1);
        }
        
        if (bracket_pos == data.size() - 1)
        {
            left_side = data.substr(1, bracket_pos - 1);

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
            
            return;
        }
        
        
        position = data.find_first_of(";&|", bracket_pos + 1);
        
        
        char seperater = data.at(position);
        
        if (seperater != '&' && seperater != '|' && seperater != ';')
        {
            position -= 1;
            seperater = data.at(position);
        }

        if (seperater == ';')
        {
            string left_side;
            string right_side;
            
            if (position == data.size() - 1)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = data.substr((position + 2));   
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
        else if (seperater == '&')
        {
            
            string left_side;
            string right_side;
            
            if (position == data.size() - 2)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = data.substr((position + 3));   
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
        else if (seperater == '|')
        {
            string left_side;
            string right_side;
            
            if (position == data.size() - 2)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = data.substr((position + 3));  
                
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
    //**IMPORTANT** END OF CHECKING ()
    else if (data.at(0) == '[')
    {
        string left_side;
        string right_side;
        
        if (data.find("]") != string::npos)
        {
            bracket_pos = data.find("]");
        }
        else
        {
            // do nothing
        }
        
        if (bracket_pos == data.size() - 1)
        {
            left_side = data.substr(1, bracket_pos - 1);
            
            
            if (parent->left_child == this)
            {
                temp = parent->left_child;
                parent->left_child = new Test_single(new Arg(left_side));
                parent->left_child->parent = temp->parent;

                parent->left_child->left_child->parse();
            }
            else
            {
                temp = parent->right_child;
                parent->right_child = new Test_single(new Arg(left_side));
                parent->right_child->parent = temp->parent;
                
                parent->right_child->left_child->parse();
            }
            
            return;
        }
        
        
        position = bracket_pos + 2;
        while (position > data.size() - 1)
        {
            position -= 1;
        }
        
        
        char seperater = data.at(position);
        
        if (seperater != '&' && seperater != '|' && seperater != ';')
        {
            position -= 1;
            seperater = data.at(position);
        }

        if (seperater == ';')
        {
            string left_side;
            string right_side;
            
            if (position == data.size() - 1)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(0, bracket_pos - 1);
                right_side = data.substr((position + 2));   
            }
            
            
            
            //found the character then seperated into two strings then make a new 
            //node based on if we are working with the right or left child
            if (parent->left_child == this)
            {
                temp = parent->left_child;
                parent->left_child = new Test_semicolon(new Arg(left_side), new Arg(right_side));
                parent->left_child->parent = temp->parent;
                
                parent->left_child->left_child->parse();
                parent->left_child->right_child->parse();
            }
            else
            {
                temp = parent->right_child;
                parent->right_child = new Test_semicolon(new Arg(left_side), new Arg(right_side));
                parent->right_child->parent = temp->parent;
                
                parent->right_child->left_child->parse();
                parent->right_child->right_child->parse();
            }
            
            delete temp;
            
        }
        //seperate by a &&
        else if (seperater == '&')
        {
            
            string left_side;
            string right_side;
            
            if (position == data.size() - 2)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = data.substr((position + 3));   
            }
            
            
            //found the character then seperated into two strings then make a new 
            //node based on if we are working with the right or left child
            if (parent->left_child == this)
            {
                temp = parent->left_child;
                parent->left_child = new Test_and(new Arg(left_side), new Arg(right_side));
                parent->left_child->parent = temp->parent;
                
                parent->left_child->left_child->parse();
                parent->left_child->right_child->parse();
            }
            else
            {
                temp = parent->right_child;
                parent->right_child = new Test_and(new Arg(left_side), new Arg(right_side));
                parent->right_child->parent = temp->parent;
                
                parent->right_child->left_child->parse();
                parent->right_child->right_child->parse();
            }
            

            delete temp;
            
        }
        //seperate by a ||
        else if (seperater == '|')
        {
            string left_side;
            string right_side;
            
            if (position == data.size() - 2)
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = " ";
            }
            else 
            {
                left_side = data.substr(1, bracket_pos - 1);
                right_side = data.substr((position + 3));  
                
            }
            
            //found the character then seperated into two strings then make a new 
            //node based on if we are working with the right or left child
            if (parent->left_child == this)
            {
                temp = parent->left_child;
                parent->left_child = new Test_or(new Arg(left_side), new Arg(right_side));
                parent->left_child->parent = temp->parent;
                
                parent->left_child->left_child->parse();
                parent->left_child->right_child->parse();
            }
            else
            {
                temp = parent->right_child;
                parent->right_child = new Test_or(new Arg(left_side), new Arg(right_side));
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
    else if (data.find("test ") != string::npos && data.at(0) == 't')
    {
        string left_side;
        string right_side;
        
        if (data.find(";") == string::npos && data.find("&&") == string::npos && data.find("||") == string::npos)
        {
            left_side = data.substr(5);

            if (parent->left_child == this)
            {
                temp = parent->left_child;
                parent->left_child = new Test_single(new Arg(left_side));
                parent->left_child->parent = temp->parent;

                parent->left_child->left_child->parse();
            }
            else
            {
                temp = parent->right_child;
                parent->right_child = new Test_single(new Arg(left_side));
                parent->right_child->parent = temp->parent;
                
                parent->right_child->left_child->parse();
            }
            
            delete temp;
            
            return;
        }
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
            
            if (left_side.at(0) == ' ' && left_side.size() > 1)
            {
                left_side = left_side.substr(1);
            }
            
            if (right_side.at(0) == ' ' && right_side.size() > 1)
            {
                right_side = right_side.substr(1);
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
            
            if (left_side.at(0) == ' ' && left_side.size() > 1)
            {
                left_side = left_side.substr(1);
            }
            
            if (right_side.at(0) == ' ' && right_side.size() > 1)
            {
                right_side = right_side.substr(1);
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
            
            if (left_side.at(0) == ' ' && left_side.size() > 1)
            {
                left_side = left_side.substr(1);
            }
            
            if (right_side.at(0) == ' ' && right_side.size() > 1)
            {
                right_side = right_side.substr(1);
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
        
        if (left_side.at(0) == ' ' && left_side.size() > 1)
        {
            left_side = left_side.substr(1);
        }
        
        if (right_side.at(0) == ' ' && right_side.size() > 1)
        {
            right_side = right_side.substr(1);
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
        
        if (left_side.at(0) == ' ' && left_side.size() > 1)
        {
            left_side = left_side.substr(1);
        }
        
        if (right_side.at(0) == ' ' && right_side.size() > 1)
        {
            right_side = right_side.substr(1);
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
        
        if (left_side.at(0) == ' ' && left_side.size() > 1)
        {
            left_side = left_side.substr(1);
        }
        
        if (right_side.at(0) == ' ' && right_side.size() > 1)
        {
            right_side = right_side.substr(1);
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
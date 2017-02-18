#include "../header/Base.h"
#include "../header/Single.h"
#include "../header/Connectors.h"
#include "../header/And.h"
#include "../header/Arg.h"
#include "../header/Or.h"
#include "../header/Semicolon.h"
#include "../header/shellprompt.h"

#include <unistd.h>
#include <iostream>
using namespace std;

int main() 
{
    string command;
    string shellUserInfo = getUserInfo();
    
    cout << shellUserInfo;
    while (getline(cin, command))
    {
        if (command != "")
        {
            Arg* first_string = new Arg(command);
            Single* top = new Single(first_string);
        
            top->parse();
        
            top->execute();
            
            
            top->delete_tree(top);
            
            
        }
        
        
        cout << shellUserInfo;
    }
    
    cout << endl;
    
    return 0;
}
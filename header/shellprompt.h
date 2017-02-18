#ifndef SHELLPROMPT_H
#define SHELLPROMPT_H

#include <unistd.h>
#include <iostream>
#include <pwd.h>
#include <limits.h>
#include <sstream>

using namespace std;

string getUserInfo()
{
   struct passwd* lgn = getpwuid(getuid()); //gets the name of the logged in userInf
   char machineName[HOST_NAME_MAX]; //creates c string for holding the machine name of the current system
   gethostname(machineName, HOST_NAME_MAX); //gets and stores the machine name
   
   stringstream userInf; //creates a stringstream
   userInf << lgn->pw_name;
   userInf << "@";
   userInf << machineName;
   userInf << "$ ";
   
   return userInf.str(); //returns contents of stringstream as string
}

#endif
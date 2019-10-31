//File Name: UserInterface.cpp
//Author: Ryan Schultz
//Email Address: schultz4@kenyon.edu
//Assignment Number: 2
//Description: Class to manage input and output between user and console
//Last Changed: October 31, 2019

#include "UserInterface.h"

//Empty constructor
UserInterface::UserInterface()
{

}

//Precondition: Program is not processing commands and is 
//ready for a new command.
//Postcondition: ">" will be output to the console 
//indicating that the program is ready for another command
void UserInterface::o_readyForCommand()
{
  cout << ">";
}

//Precondition: Player must have reached the exit room 
//and typed the command "open exit"
//Postcondition: "Game Over" will be printed to the 
//console
void UserInterface::o_gameOver()
{
  cout << "Game Over";
}

//Precondition: The container must have been opened
//Postcondition: "The container was opened" will be 
//printed to the console
void UserInterface::o_containerOpened()
{
  cout << "The container was opened";
}

//Precondition: command must be a string with allocated 
//memory
//Postcondition: A new value will be input into command 
//from the console. Command will be in all UPPER CASE.
void UserInterface::i_getCommand(string &command)
{
  cin >> command;
  transform(command.begin(), command.end(), command.begin(), ::tolower);
}

//Precondition: roomDescription will be a string containing 
//the description of a room. itemNames will be a vector of //strings representing the names of the items in the room
//Postcondition: the description of the room will be //printed to the console.
void UserInterface::o_describeRoom( string roomDescription, vector< string > itemNames )
{
  o_describe( roomDescription );
  cout << endl;
  o_roomContains();
  o_listItems( itemNames );
}

//Precondition: description will be a string describing //some object
//Postcondition: Description will be output to console.
void UserInterface::o_describe( string description )
{
  cout << description;
}

//Precondtion: none
//Postcondition: "The room contains: " will be printed to   
//the console.
void UserInterface::o_roomContains()
{
  cout << "The room contains: ";
}

//Precondition: containerName will be a string representing 
//the name of a container. itemNames will be a vector of 
//strings representing the names of the items in the 
//container.
//Postcondition: "[container] contains: " will be printed 
//followed by the names of the items in the container 
//separated by commas approapriately.
void UserInterface::o_containerContains( string containerName, vector< string > itemNames )
{
  cout << containerName << " contains: ";
  o_listItems( itemNames );
}

//Precondition: itemNames will be a vector of strings which 
//represent the names of items
//Postcondition: The names of the items will be printed 
//separated approapriately by commas
void UserInterface::o_listItems( vector< string > itemNames )
{
  if( itemNames.empty() ){
    cout << "Nothing";
  }
  else{
    int i = 0;
    while ( i < itemNames.size() )
    {
      cout << itemNames[i];
      if( i != ( itemNames.size() - 1 ) ){
        cout << ",";
      }
      cout << endl;
      i++;
    }
  }
}

//Precondition: A container that a player is trying to //access will be closed
//Postcondition: "This container is closed" will be output //to the console.
void UserInterface::o_containerIsClosed()
{
  cout << "This container is closed";
}


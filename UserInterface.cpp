#include "UserInterface.h"

//Empty constructor
UserInterface::UserInterface()
{

}

void UserInterface::o_readyForCommand()
{
  cout << ">";
}

//Precondition: Player must have reached the exit room and typed the command "open exit"
void UserInterface::o_gameOver()
{
  cout << "Game Over";
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

void UserInterface::o_describeRoom(Room room)
{
  string description = room.getDescription();
  cout << description << endl;
  int i=0;
  cout << "The room contains:" << endl;
  vector< string > items = room.getItemNames();
  while (i<items.size()) 
  {
    cout << items[i] << endl;
    i++;
  }
}

/*
void UserInterface::o_containerIsClosed()
{
  cout << "This container is closed";
}
*/

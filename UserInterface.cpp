#include "UserInterface.h"

//Empty constructor
UserInterface::UserInterface()
{

}

void UserInterface::o_readyForCommand()
{
  cout << ">";
}

void UserInterface::i_getCommand(string &command)
{
  cin >> command;
}

void UserInterface::o_describeRoom(Room room)
{
  string description = room.getDescription();
  cout << description << endl;
  int i=0;
  cout << "The room contains:" << endl;
  vector<string> items = room.getItems();
  while (i<items.size()) 
  {
    cout << items[i] << endl;
    i++;
  }
}
#include <iostream>
#include <algorithm>
#include "room.h"
#include "item.h"

using namespace std;
//The o_ prefix signifies output and the i_ prefix input
class UserInterface
{
  public:
  //constructor
  UserInterface();
  
  //output commands
  void o_readyForCommand();
  void o_describeRoom(Room room);
  void o_containerIsClosed();
  
  //input commands
  void i_getCommand(string &command);
  
  private:

};
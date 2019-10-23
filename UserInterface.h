#include <iostream>
#include "room.h"

using namespace std;
//The o_ prefix signifies output and the i_ prefix input
class UserInterface
{
  public:
  UserInterface();
  void o_readyForCommand();
  void i_getCommand(string &command);
  void o_describeRoom(Room room);

  private:
};
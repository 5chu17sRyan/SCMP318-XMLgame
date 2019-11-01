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
  void o_describeRoom( string roomDescription, vector< string > itemNames );
  void o_containerContains( string containerName, vector< string > itemNames );
  void o_describe( string description );
  void o_containerIsClosed();
  void o_gameOver();
  void o_containerOpened();
  void o_noItemFound();
  void o_unableToLeave();
  void o_creaturedKilled();

  //input commands
  void i_getCommand(string &command);
  
  private:
  void o_roomContains();
  void o_listItems( vector< string > itemNames );
};
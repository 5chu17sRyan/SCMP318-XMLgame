#include <iostream>
#define XML_USE_STL
#include "xmlParser.h"
#include <map>
#include <vector>
#include "room.h"
#include "world.h"
#include "UserInterface.h"


using namespace std;

string bookFile = "game.xml";

void processCommands(World & world, string command) 
{
  //checkBorder returns the room name bordering the current room in the direction of the command
  //w.rooms[w.location] is the current room
  Room currentRoom = world.getCurrentRoom();
  string nextRoom=currentRoom.checkBorder(command);
  if (nextRoom!="")
    world.location=nextRoom;
}


int main() 
{
  XMLNode aNode=XMLNode::openFileHelper(bookFile.c_str(),"map");
  World world=World(aNode);
  UserInterface UI = UserInterface();
  
  string command = "";
  while (1) {
    //Be careful using assignment operator on objects
    Room currentRoom = world.getCurrentRoom();
    UI.o_describeRoom(currentRoom);
    UI.o_readyForCommand();
    UI.i_getCommand(command);
    processCommands(world, command);
  }
}
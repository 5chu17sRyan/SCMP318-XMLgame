//File Name: main.cpp
//Author: Ryan Schultz
//Email Address: schultz4@kenyon.edu
//Assignment Number: 2
//Description: Program to play a simple text adventure game
//Last Changed: October 31, 2019

#include <iostream>
#define XML_USE_STL
#include "xmlParser.h"
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sstream>
#include "room.h"
#include "item.h"
#include "container.h"
#include "world.h"
#include "UserInterface.h"

////////////////////////////////////////////////////////////
using namespace std;

const string bookFile = "game.xml";

/*Precondition: world is a reference to a world object 
created at the beginning of the program. command is a 
command input by the user.*/
/*Postcondition: the functionality associated with the 
command string will be executed. This may change values in
world.*/
void processCommands( World &world, string command );

//Precondition: command must be a user command in the form 
//of a string. verb, object1, preposition, and object2 must 
//be strings with allocated memory.
//Postcondition: command will be parsed down into 
//potentially four different words representing different 
//parts of the command.
void parseCommand(string command, string& verb, string& object1, string& preposition, string& object2);

UserInterface UI = UserInterface();
Container Inventory = Container();

int main() 
{
  //Creates parent node of all other tags
  XMLNode aNode = XMLNode::openFileHelper( bookFile.c_str(), "map" );

  World world = World( aNode );
  
  string command = "";
  while (1) 
  {
    //Describes current room
    Room currentRoom = world.getCurrentRoom();
    UI.o_describeRoom( currentRoom.getDescription(), currentRoom.getItemNames());

    //Gets and executes command from user.
    UI.o_readyForCommand();
    UI.i_getCommand( command );
    processCommands( world, command );
  }

  return 0;
}

void processCommands( World& world, string command ) 
{ 
  //check single phrase commands 
  bool isMovementCommand = command == "s" || command == "w" || command == "e" || command == "n";
  bool isInventoryCommand = command == "i";
  bool isExitCommand = command == "open exit";

  //Parse words
  string verb = "";
  string object1 = "";
  string preposition = "";
  string object2 = "";
  parseCommand(command, verb, object1, preposition, object2);

  //check multi phrase commands
  bool isTakeCommand = verb == "take";
  bool isOpenCommand = verb == "open";
  bool isReadCommand = verb == "read";
  bool isDropCommand = verb == "drop";
  bool isPutCommand = verb == "put";
  bool isTurnonCommand = verb == "turn";
  bool isAttackCommand = verb == "attack";
  
  
  if( isMovementCommand )
  {
    world.moveToNewRoom( command );
  }
  if( isInventoryCommand )
  {
    UI.o_containerContains( Inventory.getName(), Inventory.getItemNames() );
  }
  if( isOpenCommand )
  {
    Room currentRoom = world.getCurrentRoom();
    Container container = currentRoom.containers[object1];
    container.open();
    UI.o_containerOpened();
    UI.o_containerContains( container.getName(), container.getItemNames() );
  }
  
  //Item in inventory commands
  if( isReadCommand )
  {
    Item item = Inventory.itemMap.at(object1);
    UI.o_describe( item.getDescription() );
  }
  if( isTurnonCommand )
  {
    string actualObject = preposition;
    Item item = Inventory.itemMap.at(actualObject);
    item.turnOn();
  }
  if( isDropCommand )
  {
    Item item = Inventory.takeItem(object1);
  }


  if( isExitCommand )
  {
    UI.o_gameOver();
    exit(0);
  }
}

void parseCommand(string command, string& verb, string& object1, string& preposition, string& object2)
{
  istringstream commandStream(command);
  commandStream >> verb;
  commandStream >> object1;
  commandStream >> preposition;
  commandStream >> object2;
}

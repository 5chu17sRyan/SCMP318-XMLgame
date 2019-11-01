//File Name: main.cpp
//Author: Ryan Schultz
//Email Address: schultz4@kenyon.edu
//Assignment Number: 2
//Description: Program to play a simple text adventure game
//Last Changed: November 1, 2019

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
  //Describes current room
  Room currentRoom = world.getCurrentRoom();
  UI.o_describeRoom( currentRoom.getDescription(), currentRoom.getItemNames());
  while (1) 
  {
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
  
  //Move Rooms
  if( isMovementCommand )
  {
    world.moveToNewRoom( command );
    Room currentRoom = world.getCurrentRoom();
    UI.o_describeRoom( currentRoom.getDescription(), currentRoom.getItemNames());
  }

  //Check Inventory
  if( isInventoryCommand )
  {
    UI.o_containerContains( Inventory.getName(), Inventory.getItemNames() );
  }

  //Open Container
  if( isOpenCommand )
  {
    Room currentRoom = world.getCurrentRoom();
    map<string, Container> roomContainers = currentRoom.getContainers();
    Container container = roomContainers.at( object1 );

    container.open();
    //cout << container.getIsOpen() << endl;

    UI.o_containerOpened();
    UI.o_containerContains( container.getName(), container.getItemNames() );
  }
  
  //Read Item
  if( isReadCommand )
  {
    map< string, Item > inventoryItems = Inventory.getItemMap();

    //If the object exists in the inventory
    if( inventoryItems.count( object1 ) > 0 ){
      Item item = inventoryItems.at( object1 );

      UI.o_describe( item.getDescription() );
    }
    else{
      UI.o_noItemFound();
    }
  }

  //Turn On Item
  if( isTurnonCommand )
  {
    string actualObject = preposition;
    map< string, Item > inventoryItems = Inventory.getItemMap();
    //If object exists in inventory
    if( inventoryItems.count( object1 ) > 0 ){
      Item item = inventoryItems.at( actualObject );

      item.turnOn();
    }
    else{
      UI.o_noItemFound();
    }
  
  }

  //Drop Item on the Floor
  if( isDropCommand )
  {
    Room currentRoom = world.getCurrentRoom();
    map< string, Item > inventoryItems = Inventory.getItemMap();
    //If object exists in inventory
    if( inventoryItems.count( object1 ) > 0 ){
      Item droppedItem = Inventory.takeItem( object1 );
      currentRoom.addItemToRoom( droppedItem );
    }
    else{
      UI.o_noItemFound();
    }
  }

  //Put Item in Container
  if( isPutCommand )
  {
    Room currentRoom = world.getCurrentRoom();
    map<string, Container> roomContainers = currentRoom.getContainers();
    Container container = roomContainers[ object2 ];
    
    //If container is open
    if( container.getIsOpen() )
    {
      map< string, Item > inventoryItems = Inventory.getItemMap();
      //If object exists in inventory
      if( inventoryItems.count( object1 ) > 0 )
      {
        Item item = Inventory.takeItem( object1 );
        container.addItem( item );
      }
      else
      {
        UI.o_noItemFound();
      }
    }
    else
    {
      UI.o_containerIsClosed();
    }
  }

  //Attack Creature with item
  if( isAttackCommand )
  {
    UI.o_creaturedKilled();
  }

  //Take Item
  if( isTakeCommand )
  {
    bool foundItem = false;
    Room currentRoom = world.getCurrentRoom();
    map< string, Item > roomItems = currentRoom.getItems();
    //If the object is in the room
    if( roomItems.count( object1 ) > 0 )
    {
      foundItem = true;
      Item item = currentRoom.takeItem( object1 );
      Inventory.addItem( item );
    }
    else
    {
      //Check all containers in the room
      vector<string> containers = currentRoom.getContainerNames();
      for( int i = 0; i < containers.size(); i++)
      {
        map<string, Container> roomContainers = currentRoom.getContainers();
        string containerName = containers.at(i);
        
        Container container = roomContainers.at(containerName);
        map<string, Item> containerItems = container.getItemMap();
        //If object is in the container
        if( containerItems.count( object1 ) > 0 )
        {
          foundItem = true;
          Item item = container.takeItem( object1 );
          Inventory.addItem( item );
        }
      }
    }

    if( !foundItem )
    {
      UI.o_noItemFound();
    }
  }

  //Exit The Dungeon
  if( isExitCommand )
  {
    Room currentRoom = world.getCurrentRoom();
    string isExit = currentRoom.getType();
    if( isExit == "exit" )
    {
      UI.o_gameOver();
      exit(0);
    }
  
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

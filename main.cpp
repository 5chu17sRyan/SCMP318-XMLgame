#include <iostream>
#define XML_USE_STL
#include "xmlParser.h"
#include <map>
#include <vector>
#include "room.h"
#include "world.h"
#include "UserInterface.h"

////////////////////////////////////////////////////////////
using namespace std;

const string bookFile = "game.xml";

void processCommands( World &world, string command );
/*Precondition: world is a reference to a world object 
created at the beginning of the program. command is a 
command input by the user.*/
/*Postcondition: the functionality associated with the 
command string will be executed. This may change values in
world.*/

void changeWorldLocation( World &world, string movementDirection );
/*Precondition: world is a reference to a world objec 
created at the beginning of the program. movementDirection
is a command (either "n", "e", "s", "w") that indicates 
the direction the player wants to try to move to.*/
/*Postcondition: If there is another room in that direction,
the location within world will be updated (player will 
move to the room in that direction). If there is no room 
in that direction notify the user.*/

int main() 
{
  //Creates parent node of all other tags
  XMLNode aNode = XMLNode::openFileHelper( bookFile.c_str(), "map" );

  World world = World( aNode );
  UserInterface UI = UserInterface();
  
  string command = "";
  while (1) 
  {
    //Describes current room
    Room currentRoom = world.getCurrentRoom();
    UI.o_describeRoom( currentRoom );

    //Gets and executes command from user.
    UI.o_readyForCommand();
    UI.i_getCommand( command );
    processCommands( world, command );
  }
}

void processCommands( World &world, string command ) 
{
  //Might move this boolean check into its own function.
  bool movementCommand = command == "s" || command == "w" || command == "e" || command == "n";
  
  if( movementCommand )
  {
    changeWorldLocation( world, command );
  }
}

/*Command functions like this might be moved into a command
class or might be moved into existing classes. For 
instance this might be moved into the world class.*/
void changeWorldLocation( World &world, string movementDirection )
{
  Room currentRoom = world.getCurrentRoom();
  string nextRoom = currentRoom.checkBorder(movementDirection);
  if( nextRoom != "" )
  {
    world.location = nextRoom;
  }
}
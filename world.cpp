#include <iostream>
#include "world.h"

World::World(XMLNode aNode) 
{
  int i=0;
  XMLNode n=aNode.getChildNode(i++);
  location="";
  do {
    string tag=n.getName();
    //cout << "World:" << tag << endl;
    if (tag == "room") {
      Room r = Room(n);
      rooms[r.name]=r;
      if (location=="") // Location will be first room
        location=r.name;
    }

    n=aNode.getChildNode(i++);
  } while (!n.isEmpty());
}

//Returns the room at the current location
Room World::getCurrentRoom()
{
  return rooms[location];
}

/*Precondition: movementDirection is a command (either 
"n", "e", "s", "w") that indicates the direction the 
player wants to try to move to.*/
/*Postcondition: If there is another room in that 
direction, the location within world will be updated 
(player will move to the room in that direction). If 
there is no room in that direction notify the user.*/
void World::moveToNewRoom(string movementDirection)
{
  Room currentRoom = getCurrentRoom();
  string nextRoom = currentRoom.checkBorder(movementDirection);
  if( nextRoom != "" )
  {
    location = nextRoom;
  }
}
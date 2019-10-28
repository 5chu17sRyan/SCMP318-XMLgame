#include <iostream>
#include "world.h"
#include <string>
#include <vector>
#include <map>

World::World(XMLNode aNode) 
{
  int i = 0;
  XMLNode n = aNode.getChildNode( i++ );
  location = "";
  do {
    string tag=n.getName();
    
    if( tag == "room" )
    {
      Room r = Room( n );
      addRoomToMap( r, rooms );
      setInitialLocation( r, location );
    }
    else if( tag == "item" )
    {
      Item i = Item( n );
      addItemToMap( i, items );
    }

    n = aNode.getChildNode( i++ );
  } while ( !n.isEmpty() );
}

/*Preconditon: room is an existing room object*/
/*Postcondition: If the location has yet to be set set 
it equal to the name of this room*/
void World::setInitialLocation(Room room, string &location )
{
  if( location == "")
  {
    location = room.name;
  }
}

/*Preconditon: room will be an existing room object*/
/*Postconditon: The room will be added into a map which 
maps from room name to the relevant room object*/
void World::addRoomToMap(Room room, map<string, Room>& rooms)
{
  rooms[room.name] = room;  
}

/*Preconditon: item will be an existing item object*/
/*Postconditon: The item will be added into a map which 
maps from item name to the relevant item object*/
void World::addItemToMap(Item item, map<string, Item>& items)
{
  items[item.name] = item;
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
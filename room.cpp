//File Name: room.cpp
//Author: Ryan Schultz
//Email Address: schultz4@kenyon.edu
//Assignment Number: 2
//Description: Class to represent a room in the world/dungeon
//Last Changed: October 31, 2019

#include <iostream>
#include "room.h"

//default constructor intializes values to empty strings
Room::Room() {
  name="";
  description="";
  type="";
}

//Constructor gets object data from XML node 
Room::Room(XMLNode aNode) {
  int i=0;
  XMLNode cNode=aNode.getChildNode(i++);

  type = "";
  do {
    string tag=cNode.getName();
    if ( tag == "name" )
      name = cNode.getText( 0 );
    else if ( tag == "description" )
      description = cNode.getText( 0 );
    else if ( tag == "type" )
      type = cNode.getText( 0 );
    else if ( tag == "item" ) {
      Item i = Item( cNode );
      addItemToMap( i, items );
      string itemName = i.name;
      itemNames.push_back( itemName );
    } else if ( tag == "border" ) {
      Border b = Border( cNode );
      borders.push_back( b );
    } else if ( tag == "container" ){
      Container c = Container( cNode );
      containers[c.getName()] = c;
    }

    cNode=aNode.getChildNode(i++);
  } while (!cNode.isEmpty());
}


/*Preconditon: item will be an existing item object*/
/*Postconditon: The item will be added into a map which
maps from item name to the relevant item object*/
void Room::addItemToMap(Item item, map<string, Item>& items)
{
 items[item.name] = item;
}

//Precondition: Room must have a type even if only empty
//Postcondition: type is returned to the program.
string Room::getType()
{
  return type;
}

//Precondition: command is a string (n, s, e, w) that 
//indicates the direction to check for a border.
//Postcondition: If there is a room in the direction of the 
//command, the name of that room is returned. Otherwise, an 
//empty string is returned.
string Room::checkBorder(string command) {
  int l = borders.size();
  string room="";
  int i=0;
  while (i<l && borders[i].command!=command) {
    i++;
  }
  if (i<l) {
    room=borders[i].name;
  }
  if (room!="") {
    cout << "Go to " << room << endl;
  } else {
    cout << "Can't go that way!" << endl;
  }
  return (room);
}

//accessor function for string description
string Room::getDescription()
{
  return description;
}

//accessor function for map<string,Item> items
map< string, Item > Room::getItems()
{
  return items;
}

//accessor function for vector<string> itemNames
vector< string > Room::getItemNames()
{
  return itemNames;
}
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
  do {
    string tag=cNode.getName();
    //cout << "Room:" << tag << endl;
    //cout << "tag:" << iName << " " << cNode.getText(0)<<  endl;
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


string Room::checkBorder(string command) {
  int l = borders.size();
  string room="";
  int i=0;
  while (i<l && borders[i].command!=command) {
    //cout << "Border Check:" << i << borders[i].name << borders[i].direction << borders[i].command << endl; 
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

string Room::getDescription()
{
  return description;
}

map< string, Item > Room::getItems()
{
  return items;
}

vector< string > Room::getItemNames()
{
  return itemNames;
}
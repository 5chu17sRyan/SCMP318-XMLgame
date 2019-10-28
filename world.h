#ifndef World_H
#define World_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>
#include <map>
#include "room.h"
#include "item.h"

using namespace std; 
class World 
{ 
  public: 
  string location;
  
  World(XMLNode aNode);

  Room getCurrentRoom();
  void moveToNewRoom(string movementDirection);

  private:
  map<string,Room> rooms;
  map<string,Item> items;

  void setInitialLocation( Room room, string &location );
  void addRoomToMap( Room room, map<string, Room>& rooms );
  void addItemToMap(Item item, map<string, Item>& items);
}; 
#endif
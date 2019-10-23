#ifndef World_H
#define World_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>
#include <map>
#include "room.h"

using namespace std; 
class World 
{ 
  public: 
  //map<string,Item> items;
  string location;
  
  World(XMLNode aNode);
  Room getCurrentRoom();

  private:
  map<string,Room> rooms;
}; 
#endif
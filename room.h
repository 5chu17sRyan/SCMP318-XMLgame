#ifndef Room_H
#define Room_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>
#include <map>
#include "border.h"
#include "item.h"
#include "container.h"

using namespace std; 
class Room 
{ 
  public: 
  string name;
  vector<Border> borders;
  
  //constructors
  Room();
  Room(XMLNode aNode);

  string checkBorder(string c);
  void addItemToRoom( Item item );
  Item takeItem( string itemName );
  
  //get functions
  string getDescription();
  map<string, Item> getItems();
  vector<string> getItemNames();
  map<string, Container> getContainers();
  vector<string> getContainerNames();
  string getType();

  private:
  string type;
  string description;
  map< string, Item > items;
  vector< string > itemNames; 
  vector< string > containerNames; 
  map< string, Container > containers;
}; 
#endif
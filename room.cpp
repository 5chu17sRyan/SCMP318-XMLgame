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
  string type;
  vector<Border> borders;
  
  //constructors
  Room();
  Room(XMLNode aNode);

  string checkBorder(string c);
  void addItemToMap(Item item, map<string, Item>& items);
  
  //get functions
  string getDescription();
  map< string, Item > getItems();
  vector< string > getItemNames();

  private:
  string description;
  map< string, Container > containers;
  map< string, Item > items;
  vector< string > itemNames;
}; 
#endif
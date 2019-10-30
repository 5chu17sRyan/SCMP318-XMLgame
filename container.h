#ifndef CONTAINER_H
#define CONTAINER_H
#define XML_USE_STL

#include "xmlParser.h"
#include "UserInterface.h"
#include <vector>
#include <string>
#include <map>
#include "item.h"

using namespace std;

class Container
{
  public:
  Container();
  Container(XMLNode aNode);

  void addItem(Item item);
  Item takeItem(string itemName);
  void open();
  
  private:
  map<string, Item> itemMap;
  bool isOpen;
  string name;
};
#endif
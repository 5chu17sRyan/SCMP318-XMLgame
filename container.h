#ifndef CONTAINER_H
#define CONTAINER_H
#define XML_USE_STL

#include "xmlParser.h"
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

  string getName();
  map<string, Item> itemMap;
  vector< string > getItemNames();

  private:
  bool isOpen;
  string name;
  vector< string > itemNames;
};
#endif
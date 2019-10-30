#ifndef ITEM_H
#define ITEM_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>

using namespace std;
class Item
{
  public:
  Item();
  Item(XMLNode aNode);
  
  string name;

  void printDescription();
  void turnOn();

  private:
  string description;
  bool isOn;
};

#endif
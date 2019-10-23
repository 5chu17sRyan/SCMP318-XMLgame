#ifndef Room_H
#define Room_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include<vector>
#include "border.h"

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
  
  //get functions
  string getDescription();
  vector<string> getItems();
      
  private:
  string description;
  vector<string> items;
}; 
#endif
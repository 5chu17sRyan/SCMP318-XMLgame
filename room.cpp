#include <iostream>
#include "room.h"

Room::Room() {
  name="";
  description="";
  type="";
}
Room::Room(XMLNode aNode) {
  int i=0;
  XMLNode cNode=aNode.getChildNode(i++);
  do {
    string tag=cNode.getName();
    //cout << "Room:" << tag << endl;
    //cout << "tag:" << iName << " " << cNode.getText(0)<<  endl;
    if (tag == "name")
      name=cNode.getText(0);
    else if (tag=="description")
      description=cNode.getText(0);
    else if (tag=="type")
      type=cNode.getText(0);
    else if (tag == "item") {
      string item=cNode.getText(0);
      //cout << "Room item:" << item << endl;
      items.push_back(item);
    } else if (tag == "border") {
      Border b = Border(cNode);
      borders.push_back(b);
    }  

    cNode=aNode.getChildNode(i++);
  } while (!cNode.isEmpty());
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

vector<string> Room::getItems()
{
  return items;
}
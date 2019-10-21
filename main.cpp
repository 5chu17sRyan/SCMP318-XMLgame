#include <iostream>
#define XML_USE_STL
#include "xmlParser.h"
#include <map>
#include <vector>
#include "room.h"
#include "world.h"


using namespace std;

string bookFile = "game.xml";

void processCommand(World & w) {
  cout << ">";
  string command;
  cin >> command;
  string nextRoom=w.rooms[w.location].checkBorder(command);
  if (nextRoom!="")
    w.location=nextRoom;
}


int main() {

  XMLNode aNode=XMLNode::openFileHelper(bookFile.c_str(),"map");

  World world=World(aNode);

  while (1) {
    cout << "loc:" << world.location << endl;
    world.rooms[world.location].describe();
    processCommand(world);
  }


  std::cout << "Hello World!\n";
}
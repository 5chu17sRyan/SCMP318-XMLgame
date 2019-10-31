//File Name: border.cpp
//Author: Ryan Schultz
//Email Address: schultz4@kenyon.edu
//Assignment Number: 2
//Description: Class to represent borders between rooms
//Last Changed: October 31, 2019

#include <iostream>
#include "border.h"

//Default constructor. Sets name to Room 1 direction to 
//north and command to an empty string. Warns that default //constructor was used.
Border::Border()
{
  cout << "Warning: Default Border constructor has been used" << endl;
  cout << "Name initialized to 'Room 1'. Direction and command have been initialized to 'north' and 'n'" << endl;
  name = "Room 1";
  direction = "north";
  command = "";
}

//Constructor using an XMLNode
Border::Border(XMLNode aNode) {
  int i=0;
  XMLNode bNode=aNode.getChildNode(i++);
  do {
    string tag=bNode.getName();
    //cout << "Border:" << tag << ":" << bNode.getText(0) << endl;
    if ( tag == "name" ) {
      name = bNode.getText( 0 );
    } else if ( tag == "direction" ) {
      direction = bNode.getText( 0 );
    } else if ( tag == "command" ) {
      command = bNode.getText( 0 );
    }
    bNode = aNode.getChildNode( i++ );
  } while ( !bNode.isEmpty() );
}
#include <iostream>
#include "item.h"

//default constructor: name+description are empty isOn=f
Item::Item()
{
  name = "";
  description = "";
  isOn = false;
}

//Constructor gets object data from XML node 
Item::Item(XMLNode aNode)
{
  int i = 0;
  XMLNode cNode = aNode.getChildNode( i++ );

  do {
    string tag = cNode.getName();
    if( tag == "name" )
    {
      name = cNode.getText( 0 );
    }
    else if( tag == "description" )
    {
      description = cNode.getText( 0 );
    }
    else if( tag == "isOn" )
    {
      isOn = cNode.getText( 0 );
    }

    cNode = aNode.getChildNode( i++ );
  } while( !cNode.isEmpty() );
}
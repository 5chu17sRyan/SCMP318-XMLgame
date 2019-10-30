#include <iostream>
#include "container.h"

//Default constructor.
Container::Container()
{
  name = "";
  isOpen = true;
}

//Precondition: XMLNode is for a container and all child nodes are items
Container::Container(XMLNode aNode)
{
  isOpen = false;
  int i = 0;
  XMLNode bNode = aNode.getChildNode( i++ );

  string tag = "";
  do 
  {
    if ( tag == "name" ) {
      name = bNode.getText( 0 );
    } 
    else if ( tag == "item" ) {
      static Item item = Item( bNode );
      string itemName = item.name;
      itemMap[ itemName ] = item; 
    }

    bNode = aNode.getChildNode( i++ );

  } while ( !bNode.isEmpty() );
}


string Container::getName()
{
  return name;
}

//Precondition: none
//Postcondition: Container is set to be open
void Container::open()
{
  bool isOpen = true;
}

//Preconditions: item is an existing item
//Postcondition: item is put in the container
void Container::addItem(Item item)
{
  if( isOpen ){
    itemMap[ item.name ] = item;
  }
  else{
    cout << "This container is closed";
  }
}

//Preconditions: itemName corresponds to a name of an 
//item
//Postconditions: item is removed from the container //and returned to the program 
Item Container::takeItem(string itemName)
{
  if( isOpen ){
    Item item = itemMap.at( itemName );
    itemMap.erase( itemName );
    return item;
  }
  else{
    cout << "This container is closed";
    Item item = Item();
    return item;
  }
}
// Headers
#include "item.h"

namespace PCPProgram
{
  unsigned short Item::numberOfItems = 0;

  // Constructor
  Item::Item(std::string& inTop, std::string& inBot) 
     : top(inTop)
     , bot(inBot)
  {}

  Item::Item(const Item& item)
     : top(item.getTop())
     , bot(item.getBot())
  {}
}

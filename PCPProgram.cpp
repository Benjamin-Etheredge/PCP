#include "PCPProgram.h"

namespace PCPProgram
{

int PCPSolver::topMaxIncrease = 0;
int PCPSolver::botMaxIncrease = 0;
int PCPSolver::remainingTurns = 0;

ItemList PCPSolver::root = ItemList();
SkeletonList PCPSolver::tree = SkeletonList();
SkeletonList PCPSolver::branch = SkeletonList();
ConfigurationsMapping PCPSolver::knownConfigurations = ConfigurationsMapping();

bool canComplete(std::string top, std::string bot, int botMaxIncrease, int topMaxIncrease, int remainingTurns)
{
   //cout << "in canComplete\n\n";
   bool canComplete = true;

   // check if it has room to complete
   if (top.length() > bot.length())
   {
      if (top.length() - bot.length() > (botMaxIncrease * remainingTurns))
      {
          // Cant reach the end
          canComplete = false;
      }
      else 
      {
      }
   }
   else if (top.length() < bot.length())
   {
      if (bot.length() - top.length() > (topMaxIncrease * remainingTurns))
      {
         canComplete = false;
      }
      else
      {
         // do nothing
      }
   }
   if (canComplete) // dat short circuit
   {
      if(top.find(bot) != 0 && bot.find(top) != 0) // check if either string is a substring starting on position 0
      {
         canComplete = false;
      }
      else
      {
         // Do nothing.
      }
   }
   return canComplete;
}

// Name reconstructItem
// Input: Skeleton& - reference to a item needed construction
//        string& reference to string asdfasdf 
// TODO: comment better
std::string reconstructItem(Skeleton& item, string& top, string& bot)
{
   // clean input
   top = "";
   bot = "";

   for (
         Skeleton::iterator iter = item.begin(),
               end = item.end();
         iter != end;
         ++iter
       )
   {
      top += (*iter)->getTop();
      bot += (*iter)->getBot();
   }
   return top + "," + bot;
}

std::string reconstructItem(Skeleton& item)
{
   string top,bot;
   return reconstructItem(item, top, bot);
}

bool PCPSolver::isCompletableItemDuplicate(ConfigurationsMapping& configs, std::string top, std::string bot)
{
   
      if (top.length() > bot.length())
      {
         top.erase(0, bot.length());
         bot = "";
      }
      else
      {
         bot.erase(0, top.length());
         top = "";
      }
   return !(configs.find(top + "," + bot) == configs.end());

}

bool insertAtEnd(SkeletonList& items, Skeleton& domino, std::string config)
{
   //insertLock.lock();
   items.push_back(domino, config);
   //insertLock.unlock();
}

// TODO: Maybe Make cleaner? nah
void isSolution(std::string top, std::string bot)
{
   //cout << "In isSolution\n" << "Top: " << top << "\nBot: " << bot << "\n\n";
   if (top.compare(bot) == 0)
   {
      cout << "Solution found \n";
     // cout << "Bound Items: " << itemSkeleton.size() << endl;
      // cout << "Item Combination: " << 
      cout << "Top: " + top << std::endl;
      cout << "Bot: " + bot + "\n";
      exit(0);
   }
}

// Create new Skeleton
Skeleton makeNewSkeleton(Item& rootItem, Skeleton& item)
{
  Skeleton tempDom(item);
  tempDom.push_back(&rootItem);
  return tempDom;
}

bool PCPSolver::generateBranch(Skeleton& partOfTree)
{
   //cout << "in generateBranch\n\n";
   // TODO: decide on if i'm going to go oop or just pass around all the time.
   for
      (
         ItemList::iterator iter = root.begin(), end = root.end();
         iter != end;
         ++iter
      )
   {
      Skeleton tempItemSkeleton = makeNewSkeleton((*iter), partOfTree);
      std::string top, bot;
      top = bot = "";
      reconstructItem(tempItemSkeleton, top, bot);
      //if (canComplete(*tempItemSkeleton) && !isDuplicate(branch, *tempDominoSkeleton))
      if (canComplete(top, bot, topMaxIncrease, botMaxIncrease, remainingTurns) 
            && !isCompletableItemDuplicate(knownConfigurations, top, bot))
      {
         isSolution(top, bot); // TODO: should maybe make this more elegant, but this is just too much faster 
         addToKnownConfigurations(top, bot);
         branch.push_back(tempItemSkeleton);
      }
      else 
      {
         //delete tempItemSkeleton;
         // do nothing
      }   
   }
}

bool PCPSolver::generateBranches()
{
   //cout << "Generating new branch. RemainingTurns: " << remainingTurns << "\n";
   int size = tree.size();
   while (size-- > 0) // should work? TODO: make sure it does
   {
      generateBranch(tree.front());
      //delete &(tree.front());
      tree.front().clear();
      tree.pop_front(); // could be faster by not returning element?
   }

   tree.swap(branch); // empty branches values into tree
}

void PCPSolver::readFile(string fileName)
{
   //cout << "In Read File, openning file\n";
   ifstream inFile(fileName);
   if (inFile)
   {
      // read
      std::string inString;
      // std::getline(inFile, inString);
      int numberOfItems; // = stoi(inString);
      inFile >> remainingTurns >> numberOfItems;
      //cout << "NumberOfItems: " << numberOfDominos << endl;
      //cout << "RemainingTurns: " << numberOfItems << endl;
     
      //cout << endl << "Input Items" << endl; 
      while (numberOfItems-- > 0)
      {
         std::string top, bot;
         inFile >> top >> bot;
         //cout << top << "," << bot << endl;
         root.push_back(Item(top,bot));
      }
      // set up reamiaing turns
      // TODO
      // set up root
      // TODO
     // intialize max increase values
      topMaxIncrease = 0;
      botMaxIncrease = 0;      
      for (ItemList::iterator iter = root.begin(), end = root.end();
            iter != end;
            ++iter)
      {
         int topLength = iter->getTop().length();   
         int botLength = iter->getBot().length();
         
         if (topLength > botLength && (topMaxIncrease < (topLength - botLength)))
         {
            topMaxIncrease = topLength - botLength;
         }
         else if (topLength < botLength && (botMaxIncrease < (botLength - topLength)))
         {
            botMaxIncrease = botLength - topLength;
         }
         else
         {
            // do nothing
         }
      }
      //cout << "TopMaxIncrease: " << topMaxIncrease << endl;
      //cout << "BotMaxIncrease: " << botMaxIncrease << endl << endl;

   }
}

void PCPSolver::run(string fileName)
{
   //root = new list<Item>();
   //tree = new list<Skeleton >();
   //branch = new list<Skeleton >()
   //cout << "In run, calling readFile\n";
   readFile(fileName);
   //cout << "Finished readFile" << endl << endl;
   // TODO: determin if need to intialize tree and branch here
   // TODO: move to different function
   
   for
      (
         ItemList::iterator iter = root.begin(),
         end = root.end();
         iter != end;
         ++iter
      )
   {
      Skeleton temp = Skeleton();
      //Item* tempPoint = &(*iter);
      temp.push_back(&(*iter));
      tree.push_back(temp);
   }
 
   for (int currentTurn = 0; remainingTurns > 0; ++currentTurn, --remainingTurns)   
   {
      cout << "Making generation: " << currentTurn + 1 << endl;
      cout << "Generation size: " << tree.size() << endl;
      //cout << "Generation Memory usage: " <<
      generateBranches();
   }
   cout << "NO SOLUTION FOUND" << endl;
}// end function run

void PCPSolver::addToKnownConfigurations(std::string top, std::string bot)
{
   if (top.length() > bot.length())
   {
      top.erase(0, bot.length());
      bot = "";
   }
   else
   {
      bot.erase(0, top.length());
      top = "";
   }
   knownConfigurations.insert(std::pair<std::string,bool>(top + "," + bot, true));
}
} // end namespace PCPProgram

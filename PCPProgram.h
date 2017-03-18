


#include "item.h"
#include <mutex>
#include <list>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

namespace PCPProgram
{




   typedef std::list<Item> ItemList;         // List of Item class
   typedef std::list<Item*> Skeleton;        // List of pointers to desired base clase
   typedef std::list<Skeleton> SkeletonList; // List of list of pointers to desired base class
   typedef std::map<std::string,bool> ConfigurationsMapping;
   
  // typedef std::forward_list<KnownConfigurations;   

   class PCPSolver
   {
      private:
         // Maximum amount the length of the top and bottem can increase
         static int topMaxIncrease;
         static int botMaxIncrease;

         static int remainingTurns;

         static ItemList root; //= new list<Item>;
         static SkeletonList tree; // = new list<list<Item*>>;
         static SkeletonList branch; // = new list<list<*Item>>;

         static ConfigurationsMapping knownConfigurations;
      
         // Disallow compiler defaultly generated features 
         PCPSolver();
         // insert others      

      public:
         //ItemProgram(string fileName);
         static void run(std::string filename);

         static bool generateBranches();
         static bool generateBranch(Skeleton& partOfTree);
         //static list<Item*>* makeNewItem(Domino& rootDomino, list<Domino*>& domino);

         // Dereference pointer and construct domino
         // Returns: execution success
         // Determins if domino is dublicate
         //static bool isDublicate(list<list<Item*> >& dominos, list<Item*>& domino);
      
         static bool isCompletableItemDuplicate(ConfigurationsMapping& items, std::string top, std::string bot);
         
         static void readFile(std::string fileName);  
         // Getters and setters
         // dont think i need any

         static void addToKnownConfigurations(std::string top, std::string bot);

//TODO TODO TODO TODO TODO
//TODO TODO TODO TODO TODO
// remove uneeded calls that clutter code. OOP OOP OOP OOP

   }; // end class PCPSolver

   std::string reconstructItem(Skeleton& domino);
   std::string reconstructItem(Skeleton& domino, std::string& top, std::string& bot);
   // Determins if the Item Compelation can reach completion;
   bool canComplete(std::string top, std::string bot, int topMaxIncrease, int botMaxIncrease, int remainingTurns);
   void isSolution(std::string top, std::string bot);

   Skeleton makeNewSkeleton(Item& rootItem, Skeleton& domino);
   bool insertAtEnd(SkeletonList& skeletons, Skeleton& skelton);
} // end namespace PCPProgram

#include <string>
namespace PCPProgram
{
// Class for holding information relating to PCP problems
class Item
{
   private:
      const std::string top;
      const std::string bot;

      // Ease of use naming members
      static unsigned short numberOfItems;
//      const unsigned short itemNumber;

      // Disable Functionality
      Item(); 
      Item(const Item&, const Item&); 
      Item operator=(const Item&);

   public:
      // Constructor
      Item(std::string& inTop, std::string& inBot);
      Item(const Item& item);

      // Getters and Setters
      const std::string getTop() const { return this->top; }
      const std::string getBot() const { return this->bot; }
};
}

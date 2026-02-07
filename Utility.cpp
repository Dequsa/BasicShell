#include "Utility.h"

namespace UtilityFunctions
{
   void DisplayHelpInfo(const std::string arg)
   {
      static std::unordered_map<std::string, int> functions_help = 
      {
        {"ls", 0},
        {"cd", 1}
      };

      int function_code = -1;

      if (functions_help.count(arg))
      {
        function_code = functions_help[arg]; 
      }
      else 
      {
        std::cout << "Error: " << "UKNOWN COMMAND\n";
      }
    
      switch(function_code)
      {
         case 0:
          std::cout <<"Error ls\n";
         break;
      }
   }
}

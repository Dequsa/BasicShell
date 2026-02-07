#include "ShellCommands.h"
#include <filesystem>
#include "Utility.h"
namespace fs = std::filesystem;

namespace ShellCommands
{
  void ListFiles(const std::vector<std::string> &args)
  {
    std::string path;

    if(args.size() < 2)
    {
      path = ".";
    }
    else
    {
      path = args[1];
    }

   for(const auto entry : fs::directory_iterator(path))
   {
      if(true)
      {
        std::cout << entry.path() << ' ';
      }
  //  else
  //  {
  //   int last_symbol_iterator = path.length() - 1;
  //   char last_symbol = entry.path().string()[last_symbol_iterator];
  //
  //   if(last_symbol == '/' && entry.path().string()[last_symbol + 1] != '.' || last_symbol != '/' && last_symbol == '.')
  //   {
  //     std::cout << entry.path() << '\n';
  //   }
  //  }
   }
  }

  void ChangeDirection(const std::vector<std::string> &args)
  {
  }
}

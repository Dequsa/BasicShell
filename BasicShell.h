#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <iterator>
#include "ShellCommands.h"

using CommandFunctions = std::function<void(const std::vector<std::string>&)>; 

namespace CheckFunctions
{
}

namespace ErrorCodes
{
}

enum class COLORS
{
  BLUE,
  RED,
  GREEN
};

class BasicShell {
public:
  
  BasicShell(char *start_argument) : start_line_symbol('>'), color(COLORS::BLUE) // default
  {
    if(*start_argument == 'h')
    {
      // tell user how this works
    }
    // load config files
    //
    //
    // start the loop of working right
    Listner();
  }
  ~BasicShell()
  {
  }

private:
  char start_line_symbol;
  COLORS color;
  std::string buffer;
  std::vector<std::string> arguments; // command argument
  std::vector<std::string> saved_buffers; // for saving buffer to use upper arrow or down arrow to navigate the saved saved_buffers
                                          //
  // umap of string : functioncall that accepts vector of strings e.g: ls -a
  std::unordered_map<std::string, CommandFunctions> shell_functions = {
    {"ls", ShellCommands::ListFiles}
  }; 

  void DisplayHelpInfo()
  {
    std::cout << "Foo Foe\n";
  }

  void TakeUserInput()
  {
    std::cout << start_line_symbol << ' ';
    std::getline(std::cin, buffer);

    if (buffer == "")
    {
      DisplayHelpInfo();
      return;
    }
  }

  void ParseUserInput()
  {
    using namespace std;
    const char BLANK_SPACE = ' ';
    string temp;
    
    // set up the variables for change
    arguments.clear();

    istringstream stream(buffer);
    // get the arguments for the command e.g ls -a ~/Desktop
    while(getline(stream, temp, BLANK_SPACE))
    {
      if (!temp.empty())
      {
        arguments.push_back(temp);
      }
    }
  }

  void ChooseFunction(int &status)
  {
    if (shell_functions.count(arguments[0]))
    {
      // [just the command name e.g ls](the command argument e.g -a)
      shell_functions[arguments[0]](arguments);
    }
  }
    
  void Listner()
  {
    int status = 1; // 1 working 0 exit
    do
    {
    TakeUserInput();
    ParseUserInput();
    ChooseFunction(status);
    }while (status);
  }
};



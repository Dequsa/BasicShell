#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <iterator>
#include <signal.h>
#include "ShellCommands.h"
#include "TaskManager.h"

using CommandFunctions = std::function<void(const std::vector<std::string>&)>; 
namespace fs = std::filesystem;

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
  }
  ~BasicShell()
  {
  }

  void Run()
  {
    Listner();
  }

private:
  char start_line_symbol;
  COLORS color;
  std::string buffer;
  std::vector<std::string> arguments; // command argument
  std::vector<std::string> saved_buffers; // for saving buffer to use upper arrow or down arrow to navigate the saved saved_buffers
  int status;
  fs::path current_dir;

  // umap of string : functioncall that accepts vector of strings e.g: ls -a
  std::unordered_map<std::string, CommandFunctions> shell_functions = {
    {"mls", ListFilesFunctions::ListFiles},
    {"exit", [this](const std::vector<std::string>&placeholder){status = 0;}},
    {"cd", ChangeDirectoryFunctions::ChangeDirectory}
  };

  void DisplayHelpInfo()
  {
    std::cout << "Foo Foe\n";
  }

  void UpdateCurrentDirection()
  {
    current_dir = fs::current_path();

    const char *raw_home_dir = std::getenv("HOME");

    if (raw_home_dir)
    {
      fs::path home_path = raw_home_dir;

      std::string crr_str = current_dir.string();
      std::string home_str = home_path.string();

      if (crr_str.find(home_str) == 0)
      {
        current_dir = "~" + crr_str.substr(home_str.length());
      }
    } 
  }

  bool CheckIfIsWhiteSpace(const std::string &str)
  {
    for (int i = 0; i < str.length(); ++i)
    {
      if(!std::isspace(str[i]))
      {
        return false;
      }
    }

    return true;
  }

  void TakeUserInput()
  {
    UpdateCurrentDirection();
  std::cout << current_dir.string() << ' ' <<start_line_symbol;
    std::getline(std::cin, buffer);

    if (buffer == "" || CheckIfIsWhiteSpace(buffer))
    {
      DisplayHelpInfo();
      buffer = "DEQUSA";
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
    else
    {
      TaskManagerFunctions::LaunchProgram(arguments);
    }
  }

  void Listner()
  {
    
    status = 1; // 1 working 0 exit
    do
    {
    TakeUserInput();
    ParseUserInput();
    ChooseFunction(status);
    }while (status);
  }
};



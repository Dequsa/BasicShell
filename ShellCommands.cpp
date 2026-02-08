#include "ShellCommands.h"
#include <filesystem>
#include "Utility.h"
namespace fs = std::filesystem;

namespace ListFilesFunctions
{
  std::string DontShowHiddenFiles(const std::filesystem::directory_entry entry)
  {
    std::string output_path = entry.path().filename().string();
    return output_path;
  }

  void ShowHiddenFiles(const std::filesystem::directory_entry entry)
  {
    std::string output_path = DontShowHiddenFiles(entry); // i know its messy but does the job if it works leave it :)
    std::cout << output_path << '\n';
  }

  void ListOneFilePerLine(const std::filesystem::directory_entry entry)
  {
    std::cout << DontShowHiddenFiles(entry) << '\n';
  }

  void ChooseDisplayFormat(const std::filesystem::directory_entry entry, const std::string option)
  {
    if(option == "-a") // show all files
    {
      ShowHiddenFiles(entry);
    }
    else if (option == "-1")
    {
      ListOneFilePerLine(entry);
    }
  }

  bool CheckIfPathExists(const std::string path)
  {
    bool fiel_path_exist = fs::exists(path);

    return fiel_path_exist;
  }

  bool IsStringAPath(const std::string str)
  {
    return str[0] == '/';
  }

  bool IsStringAnOption(const std::string str)
  {
    return str[0] == '-';
  }

  std::string ParsePath(const std::vector<std::string> &args, const std::string path)
  {
    if(args.size() < 2) // when path and maybe option
    {
      return path;
    }
    else if (!IsStringAnOption(args[1])) // when path is real path like / not .
    {
      return args[1];
    }
    else // when user doenst type path but puts a command e.g: -a
    {
      return path;
    }
  }

  void ListFiles(const std::vector<std::string> &args)
  {
    std::string path = ".";
    
    path = ParsePath(args, path);

    if (!CheckIfPathExists(path)) {
      std::cout << "Such directory doesnt exist.";
      return;
    }

    for(const auto entry : fs::directory_iterator(path))
    {
      if (args.size() < 2 || (!IsStringAnOption(args[1]) && args.size() == 2)) // check only when there is ls OR check only when there is a valid path
      {
        std::cout << DontShowHiddenFiles(entry) << '\n';
        continue;
      }
      else if (IsStringAnOption(args[1])) // check onyl when there is option no path
      {
        ChooseDisplayFormat(entry, args[1]);
      }
      else if (IsStringAnOption(args[2])) // check when there is a path and option
      {
        ChooseDisplayFormat(entry, args[2]);
      }
      else
      {
        std::cout << "Unexpected Error in ListingFiles function ShellCommands.cpp";
      }
    }
  }
}
namespace ChangeDirectionFunctions
{
  void ChangeDirection(const std::vector<std::string> &args)
  {
  }
}

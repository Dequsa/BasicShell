#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace ListFilesFunctions
{
  void ListFiles(const std::vector<std::string> &args);
}

namespace ChangeDirectoryFunctions 
{
  void ChangeDirectory(const std::vector<std::string> &args);
}

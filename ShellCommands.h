#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace ShellCommands
{
  void ListFiles(const std::vector<std::string> &args);

  void ChangeDirection(const std::vector<std::string> &args);
}

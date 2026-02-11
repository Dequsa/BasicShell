#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
#include <iostream>
#include "signal.h"
#include "TaskManager.h"

namespace TaskManagerFunctions
{

  std::vector<char*> ConvertIntoCArray(const std::vector<std::string> &args)
  {
    std::vector<char*> c_proccess_name;

    for (const auto &arg : args)
    {
      c_proccess_name.push_back(const_cast<char*>(arg.c_str()));
    }
    c_proccess_name.push_back(nullptr);

    return c_proccess_name;
  }


  void LaunchProgram(const std::vector<std::string> &args)
  {
    // WIP check if the args[0] is existing

    if(args[0] == "DEQUSA")
    {
      return;
    }

    signal(SIGINT, SIG_DFL);

    int pid = fork(); // creates a hard copyy of the parent into child

    // the child
    if (pid == 0)
    {
      // run the program
      std::vector<char*> c_name = ConvertIntoCArray(args);
      execvp(c_name[0], c_name.data());

      std::cerr << "Command not found: " << args[0] << '\n';
      exit(1);
    }
    else if(pid < 0)  // no mem
    {
      std::cerr << "Failed to fork proccess!\n";
    }
    else
    {
      int status;
      waitpid(pid, &status, 0);

      if (WIFEXITED(status)) // good ending
      {
        int exit_code = WEXITSTATUS(status);
        if (exit_code != 0)
        {
          std::cerr << "Proccess ended with value: " << exit_code << '\n';
        }
      }
      else if (WIFSIGNALED(status)) // murder ending
      {
        std::cerr << "Proccess killed by signal: " << WTERMSIG(status) << '\n';
      }
    }
  }
}

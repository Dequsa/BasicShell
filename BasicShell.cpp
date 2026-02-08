#include "BasicShell.h"

int main(int argc, char *argv[])
{
  BasicShell Shell(argv[1]);
  Shell.Run();
  return 0;
}

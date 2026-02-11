#include "BasicShell.h"

int main(int argc, char *argv[])
{
  signal(SIGINT, SIG_IGN);
  BasicShell Shell(argv[1]);
  Shell.Run();
  return 0;
}

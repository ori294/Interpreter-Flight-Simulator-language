#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
using namespace std;

int main() {

  Command *c = new OpenServerCommand();
  Command * test = new connectControlClient();
  list<string> l;
  l.emplace_back("s");
  l.emplace_back("5402");
  list<string>::iterator i= l.begin();
  //c->execute(l, i);
  test->execute(l,i);
  return 0;
}

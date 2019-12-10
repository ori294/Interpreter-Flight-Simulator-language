#include "Command.h"
#include "OpenServerCommand.h"
using namespace std;

int main() {
  Command *c = new OpenServerCommand();
  list<string> l;
  c->execute(l);
  return 0;
}
#include <iostream>
#include <list>
#include "Lexer.h"
#include "SimulatorManager.h"

int main() {

  Lexer lexer;
  std::string fileName = "test.txt";
  std::list<std::string> lexedList = lexer.readFile(fileName);
  auto iter = lexedList.begin();

  while (iter != lexedList.end()) {
    std::cout << *iter << ";";
    iter++;
  }

  cout << endl;
  SimulatorManager *sim = SimulatorManager::getInstance();
  sim->setStringList(lexedList);
  sim->runSimulator();
  return 0;
}
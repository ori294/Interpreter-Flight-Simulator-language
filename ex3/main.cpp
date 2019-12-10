#include <iostream>
#include <list>
#include "Lexer.h"

int main() {

  Lexer lexer;

  std::string fileName = "test.txt";
  std::list<std::string> lexedList = lexer.readFile(fileName);
  auto iter = lexedList.begin();

  while (iter != lexedList.end()) {
    std::cout << *iter << ", ";
    iter++;
  }
  return 0;
}
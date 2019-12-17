//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__SIMULATORMANAGER_H_
#define EX3__SIMULATORMANAGER_H_
#include "Parser.h"
#include <iostream>
#include <map>
#include "SymbolTableValue.h"
#include "Expressions/Expression.h"
#include "Expressions/ExpressionKinds.h"

class SimulatorManager
{
 private:
  /* Here will be the instance stored. */
  static SimulatorManager* instance;
  Parser *parser;
  std::map<std::string, SymbolTableValue*> symbolTable;
  //another symboltable here (local variables)
  //members: Srv client, st
  /* Private constructor to prevent instancing. */
  SimulatorManager();

 public:
  /* Static access method. */
  static SimulatorManager* getInstance();
  void update_symbol_table(std::string VarName, bool bindDirction, std::string simAddress);
  void runSimulator();
  void setStringList(std::list<std::string> strList);
  std::map<std::string, SymbolTableValue*>* getSymbolMap() {
    return &symbolTable;
  }
  ~SimulatorManager() {
    //Delete the parser
    delete this->parser;
    //Before closing the runner - delete symbols in symbol table.
    auto iter = symbolTable.begin();
    while (iter != symbolTable.end()) {
      delete iter->second;
    }
  }
};

#endif //EX3__SIMULATORMANAGER_H_

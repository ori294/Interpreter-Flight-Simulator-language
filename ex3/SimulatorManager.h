//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__SIMULATORMANAGER_H_
#define EX3__SIMULATORMANAGER_H_
#include "Parser.h"
#include <iostream>
#include <map>
#include "Commands/ConditionParser.h"
#include "SymbolTableValue.h"
#include "Expressions/Expression.h"
#include "Expressions/ExpressionKinds.h"

class SimulatorManager {
 private:
  /* Here will be the instance stored. */
  class OpenServerCommand *server;
  class connectControlClient *client;
  static SimulatorManager *instance;
  class Parser *parser;
  std::map<std::string, SymbolTableValue *> symbolTable;
  std::map<std::string, float> localSymbolTable;
  bool is_end = false;
  /* Private constructor to prevent instancing. */
  SimulatorManager();

 public:
  /* Static access method. */
  static SimulatorManager *getInstance();
  void update_symbol_table(std::string VarName, bool bindDirction, std::string simAddress);
  void runSimulator();
  bool check_end();
  void finish();
  void setStringList(std::list<std::string> strList);
  void set_server(OpenServerCommand *ser);
  void set_client(connectControlClient *cli);
  OpenServerCommand *get_server();
  connectControlClient *get_client();

  std::map<std::string, SymbolTableValue *> *getSymbolMap() {
    return &symbolTable;
  }
  std::map<std::string, float> *getLocalSymbolMap() {
    return &localSymbolTable;
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

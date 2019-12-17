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
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"

class SimulatorManager {
 private:
  /* Here will be the instance stored. */
  OpenServerCommand *server;
  connectControlClient *client;
  static SimulatorManager *instance;
  Parser *parser;
  std::map<std::string, SymbolTableValue *> symbolTable;
  /* Private constructor to prevent instancing. */
  SimulatorManager();

 public:
  /* Static access method. */
  static SimulatorManager *getInstance();
  void update_symbol_table(std::string VarName, bool bindDirction, std::string simAddress);
  void runSimulator();
  void setStringList(std::list<std::string> strList);
  void set_server(OpenServerCommand *ser);
  void set_client(connectControlClient *cli);
  OpenServerCommand *get_server();
  connectControlClient *get_client();
  std::map<std::string, SymbolTableValue *> *getSymbolMap() {
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

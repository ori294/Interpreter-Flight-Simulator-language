//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_
#include "Commands/Command.h"
#include "Commands/SingleCommands.h"
#include <unordered_map>
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/VarAssignCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/DefineLocalVarCommand.h"
#include "Commands/LoopCommand.h"

class Parser {
  std::list<std::string> commandList;
  std::list<std::string>::iterator listIterator;
  std::unordered_map<std::string, Command*> commandMap;

 public:
  std::pair<Command*,std::list<std::string>> getNextCommand();
  bool isEnded();
  Parser(std::list<std::string> strList);
  ~Parser() {
    //Before deleting the parser - delete commands in the parser;
    auto iter = commandMap.begin();
    while (iter != commandMap.end()) {
      delete iter->second;
    }
  }
};

#endif //EX3__PARSER_H_

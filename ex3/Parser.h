//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_
#include <unordered_map>
#include "Commands/Command.h"
#include "Commands/SingleCommands.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/VarAssignCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/DefineLocalVarCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/ConditionParser.h"

class Parser {
 protected:
  std::list<std::string> commandList;
  std::list<std::string>::iterator listIterator;
  std::unordered_map<std::string, Command*> commandMap;

 public:
  std::pair<Command*,std::list<std::string>> getNextCommand();
  bool isEnded();
  void startOver() {this->listIterator = this->commandList.begin();}
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

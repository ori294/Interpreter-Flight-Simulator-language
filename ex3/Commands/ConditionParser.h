//
// Created by ori294 on 12/18/19.
//

#ifndef EX3_COMMANDS_CONDITIONPARSER_H_
#define EX3_COMMANDS_CONDITIONPARSER_H_

#include "Command.h"
#include "VarAssignCommand.h"

class ConditionParser: public Command {

  std::list<std::string> commandList;
  std::list<std::string>::iterator listIterator;
  std::unordered_map<std::string, Command*> commandMap;

 public:
  std::pair<Command*,std::list<std::string>> getNextCommand();
  bool isEnded();
  ConditionParser(std::list<std::string> strList);
  ~ConditionParser() {
    //Before deleting the ConditionParser - delete commands in the parser;
    auto iter = commandMap.begin();
    while (iter != commandMap.end()) {
      delete iter->second;
    }
  }

  int execute(std::list<std::string> L) override {
  }
  int get_num_of_arg() override {

  }
};

#endif //EX3_COMMANDS_CONDITIONPARSER_H_

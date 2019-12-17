//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_
#include "Commands/Command.h"
#include "Commands/SingleCommands.h"
#include <unordered_map>

class Parser {
  std::list<std::string> commandList;
  std::list<std::string>::iterator listIterator;
  std::unordered_map<std::string, Command*> commandMap;
  std::pair<Command*,std::list<std::string>> getNextCommand();
  bool isEnded();

 public:
  Parser(std::list<std::string> strList);
  ~Parser();
};

#endif //EX3__PARSER_H_

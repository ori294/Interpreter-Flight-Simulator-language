//
// Created by ori294 on 12/10/19.
//

#ifndef EX3__LEXER_H_
#define EX3__LEXER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "string.h"
#include <stdio.h>
#include <regex>
#include <list>

/**
 * Lexer class: get a file with code and lex it into a list of strings
 */
class Lexer {
  std::list<std::string> strList;
 public:
  std::string removeBrackets(std::string str);
  std::string removeTabs(std::string str);
  std::string removeSpaces(std::string str);
  std::list<std::string> readFile(std::string fileName);
};

#endif //EX3__LEXER_H_

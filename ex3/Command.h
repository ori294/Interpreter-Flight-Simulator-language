//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_

//
// Created by gadi on 10/12/2019.
//

#ifndef INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_
#define INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_

#include <string>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>
#include "string.h"
#include <stdio.h>

/**
 * Command Interface
 */
class Command {

 public:
  virtual int execute(std::list<std::string> L) = 0;
  virtual int get_num_of_arg() = 0;
  virtual ~Command() {}
};

#endif //INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_

#endif //EX3__COMMAND_H_

//
// Created by gadi on 10/12/2019.
//

#ifndef INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_
#define INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_

#include <string>
#include <list>
using namespace std;
/**
 * Command Interface
 */
class Command {

 public:
  virtual int execute(list<string> L) = 0;
  virtual ~Command() {}
};

#endif //INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_COMMAND_H_

//
// Created by gadi on 10/12/2019.
//
#ifndef INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_
#define INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_

#include <string>
#include <iostream>
#include "Command.h"
#include <list>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
using namespace std;

class OpenServerCommand : public Command {
 private:
  thread get_info;
  //unordered_map<string, string> data_about_airplane;
 public:
  int execute(list<string> list_of_strings, list<string>::iterator indicator) override;

};

#endif //INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_

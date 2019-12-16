//
// Created by ori294 on 12/11/19.
//

#ifndef EX3__SIMULATORMANAGER_H_
#define EX3__SIMULATORMANAGER_H_
#include "Parser.h"
#include <iostream>

class SimulatorManager
{
 private:
  /* Here will be the instance stored. */
  static SimulatorManager* instance;
  Parser *parser;
  //members: Srv client, st
  /* Private constructor to prevent instancing. */
  SimulatorManager();

 public:
  /* Static access method. */
  static SimulatorManager* getInstance();
  void runSimulator();
  void setStringList(std::list<std::string> strList);
  ~SimulatorManager() {
    //delete parser
  }
};

#endif //EX3__SIMULATORMANAGER_H_

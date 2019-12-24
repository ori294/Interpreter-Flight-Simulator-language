//
// Created by ori294 on 12/18/19.
//

#include "SingleCommands.h"

/**
 * Execute the print command
 * @param comList list of arguments
 * @return return an integer type
 */
int PrintCommand::execute(std::list<std::string> comList) {

  if (std::regex_search(*comList.begin(), std::regex("[\"]"))) {
    std::cout << *comList.begin() << std::endl;
  } else {
    Expression* tempEx = SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(*comList.begin());
    std::cout << tempEx->calculate() << std::endl;

    if (tempEx != nullptr) {
      delete tempEx;
    }
  }
}

/**
 * Execute the sleep command
 * @param comList list of arguments
 * @return return an integer type
 */
int SleepCommand::execute(std::list<std::string> comList) {
  Expression* tempEx = SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(*comList.begin());
  double sleepDuration = (tempEx->calculate());
  sleep(sleepDuration/1000);

  if (tempEx != nullptr) {
    delete tempEx;
  }

  return 1;
}
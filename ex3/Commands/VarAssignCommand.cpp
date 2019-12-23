//
// Created by ori294 on 12/17/19.
//

#include "VarAssignCommand.h"

int VarAssignCommand::execute(std::list<std::string> list_of_strings) {
  /**
   * map and iterator for local var of airplane
   */
  auto localMap = SimulatorManager::getInstance()->getSymbolMap();
  auto iter1 = localMap->find(*(list_of_strings.begin()));
  auto find_match_iterator = localMap->begin();
  /**
   * map and iterator for local var that created locally
   */
  auto map_local_var = SimulatorManager::getInstance()->getLocalSymbolMap();
  auto iter3 = map_local_var->begin();
  //iterator for list of args
  auto iterator2 = list_of_strings.begin();
  iterator2++;
  string check_expression = *iterator2;
  std::regex pattern("(\\+|-|\\*|\\/)");

  //check if there are operators in the expression
  if (std::regex_search(check_expression, pattern)) {
    string numb;
    cout << "need interpret" << endl;
    std::string &str(check_expression);
    while (find_match_iterator != localMap->end()) {
      if (std::regex_search(str, std::regex(find_match_iterator->first))) {
        float value =
            SimulatorManager::getInstance()->get_server()->get_value(find_match_iterator->second->getSimAddress());
        numb = to_string(value);
        cout << "value in ariplane map: " + numb << endl;
        str = std::regex_replace(str, std::regex(find_match_iterator->first), "(" + numb + ")");
      }
      find_match_iterator++;
    }
    while (iter3 != map_local_var->end()) {
      if (std::regex_search(str, std::regex(iter3->first))) {
        float val = iter3->second;
        cout << "value in map: " + to_string(val) << endl;
        str = std::regex_replace(str, std::regex(iter3->first), "(" + to_string(val) + ")");
      }
      iter3++;
    }
    cout << str << endl;
    Interpreter *i1 = new Interpreter();
    Expression *exp = nullptr;
    exp = i1->interpret(str);
    cout << exp->calculate() << endl;
    SimulatorManager::getInstance()->get_client()->add_commands_to_queue("set " +
        iter1->second->getSimAddress() + " " + to_string(exp->calculate()) + "\r\n");
  } else if (iter1 != localMap->end()) {
    if (iter1->second->getBind()) { //if it's (right)client-bind.
      //Here we should send the client the command
      auto iter2 = list_of_strings.begin();
      iter2++;

      SimulatorManager::getInstance()->get_client()->add_commands_to_queue("set " +
          iter1->second->getSimAddress() + " " + *iter2 + "\r\n");
    }
  }
}
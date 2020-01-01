//
// Created by ori294 on 12/19/19.
//

#include "SimulatorManager.h"
#include "ConditionParser.h"

/**
 * updateCondition: updates the newest condition, after changes in the values that might happen.
 * @param commands list of commands as strings
 * @return a new boolean type expression.
 */
Expression* ConditionParser::updateCondition(std::list<std::string>* commands) {
  auto iterator = commands->begin();
  //get left value
  double leftVal = SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(*iterator)->calculate();
  iterator++;
  //get condition symbol(==,<=, etc...)
  std::string conSymbol = *iterator;
  iterator++;
  //get right value
  double rightVal = SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(*iterator)->calculate();

  Expression* cond = new BooleanOperator(new Value(leftVal), conSymbol, new Value(rightVal));

  return cond;
}

/**
 * Check whether the condition is met
 * @return double value of 1 or 0 for true of false.
 */
double ConditionParser::isConditionSatisfied() {
  return condition->calculate();
}

/**
 * Execute: run the commands in the conditinal (while or if) command
 * @param commands
 * @return integer, -1 for error
 */
int ConditionParser::execute(std::list<std::string> commands) {
  startOver(4);
  while (!parser->isEnded()) {
    auto tempPair = parser->getNextCommand();
    if (tempPair.first != nullptr && tempPair.first->get_num_of_arg() != -1) {
      tempPair.first->execute(tempPair.second);
    }
  }
  this->condition = updateCondition(&commands);
  return 0;
}

/**
 * ConditionParser CTOR
 * @param strList list of commands.
 */
ConditionParser::ConditionParser(std::list<std::string>* strList) {
  condition = updateCondition(strList);
  parser = new Parser(*strList);
  listLength = strList->size();
}

/**
 * returns the number of aruments for this conditional command
 * @return the length of the aruments list.
 */
int ConditionParser::get_num_of_arg() {
  return listLength;
}

/**
 * set the iterator to the first command in the loop
 * @param i an integer - how much to jump
 */
void ConditionParser::startOver(int i) {
  parser->startOver(i);
}

/**
 * condition parser DTOR.
 */
ConditionParser::~ConditionParser() {
  delete this->parser;
  delete this->condition;
}

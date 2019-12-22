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

  cout << "updating condition..." << endl;
  sleep(5);
  //iterator init
  auto iterator = commands->begin();

  //find the first variable in the local and global maps
  auto localSTIter = LoopLocalSymbolTable.find(*iterator);
  auto STIter = LoopSymbolTable.find(*iterator);

  float value;
  if (localSTIter != LoopLocalSymbolTable.end()) {
    value = localSTIter->second;
  } else if (STIter != LoopSymbolTable.end()) {
    if (STIter->second->getBind()) {
      value = STIter->second->getExpression()->calculate();
    } else { //value is requested from the server
      value = SimulatorManager::getInstance()->get_server()->get_value(STIter->second->getSimAddress());
    }
  } else if (Interpreter::isDouble(*iterator)) {
    value = stod(*iterator);
  }

  iterator++; //getting the condition symbol (equals, not equals, greater etc...)
  std::string conSymbol = *iterator;

  iterator++; //find the second variable in the local and global maps
  localSTIter = LoopLocalSymbolTable.find(*iterator);
  STIter = LoopSymbolTable.find(*iterator);
  float secondValue;
  if (localSTIter != LoopLocalSymbolTable.end()) {
    secondValue = localSTIter->second;
  } else if (STIter != LoopSymbolTable.end()) {
    if (STIter->second->getBind()) {
      secondValue = STIter->second->getExpression()->calculate();
    } else { //value is requested from the server
      secondValue = SimulatorManager::getInstance()->get_server()->get_value(STIter->second->getSimAddress());
    }
  } else if (Interpreter::isDouble(*iterator)) {
    secondValue = stod(*iterator);
  }

  cout << "finished updating condition..." << endl;
  //return the new boolean expression
  Expression* condition = new BooleanOperator(new Value(value), conSymbol, new Value(secondValue));
  return condition;
}

double ConditionParser::isConditionSatisfied() {
  return condition->calculate();
}

int ConditionParser::execute(std::list<std::string> commands) {
  while (!parser->isEnded()) {
    auto tempPair = parser->getNextCommand();
    if (tempPair.first->get_num_of_arg() != -1) {
      tempPair.first->execute(tempPair.second);
    }
    sleep(5);
  }
  this->condition = updateCondition(&commands);
}

ConditionParser::ConditionParser(std::list<std::string>* strList) {
  auto symbolMap = SimulatorManager::getInstance()->getSymbolMap();
  auto localMap = SimulatorManager::getInstance()->getLocalSymbolMap();
  auto symbolIterator = symbolMap->begin();
  auto localIterator = localMap->begin();

  while (symbolIterator != symbolMap->end()) {
    this->LoopSymbolTable.insert({symbolIterator->first, symbolIterator->second});
    cout << "added " << symbolIterator->first << " to the ST..." << endl;
    symbolIterator++;
  }
  while (localIterator != localMap->end()) {
    this->LoopLocalSymbolTable.insert({localIterator->first, localIterator->second});
    cout << "added " << localIterator->first << " to the Local ST..." << endl;
    localIterator++;
  }
  condition = updateCondition(strList);
  parser = new Parser(*strList);
  listLength = strList->size();
}

int ConditionParser::get_num_of_arg() {
  return listLength;
}

void ConditionParser::startOver(){
  parser->startOver();
}

ConditionParser::~ConditionParser() {

}

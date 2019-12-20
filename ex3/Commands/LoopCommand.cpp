//
// Created by ori294 on 12/18/19.
//

#include <regex>
#include "LoopCommand.h"
#include <bits/stdc++.h>

/**
 * updateCondition: updates the newest condition, after changes in the values that might happen.
 * @param commands list of commands as strings
 * @return a new boolean type expression.
 */
Expression* LoopCommand::updateCondition(std::list<std::string> commands) {
  //iterator init
  auto iterator = commands.begin();
  iterator++;

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
  } //Add else for simple number!

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
  } //Add else for simple number!

  //return the new boolean expression
  Expression* condition = new BooleanOperator(new Value(value), conSymbol, new Value(secondValue));
  return condition;
}

/**
 * Executes the loop command
 * @param commands list of commands as strings
 * @return an integer type
 */
int LoopCommand::execute(std::list<std::string> commands) {

  Expression* condition = updateCondition(commands);
  auto iterator = commands.begin();
  iterator++; iterator++; iterator++; iterator++;

  std::list<std::string> insideWhileList;
  while (iterator != commands.end()) {
    insideWhileList.emplace_back(*iterator);
  }
  this->parser = new ConditionParser(insideWhileList);

  while (condition->calculate()) {
    //make the loop
    //return condition parser to begin

    //update condition
    delete condition;
    condition = updateCondition(commands);
  }

}

/**
 * CTOR: Init local symbol table.
 * it copies the symbol tables from the main loop of the code.
 */
LoopCommand::LoopCommand() {
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
}

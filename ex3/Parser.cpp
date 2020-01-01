//
// Created by ori294 on 12/11/19.
//

#include "Parser.h"

/**
 * get the next command and returns a pair containing the command and the list of args for it.
 * @return pair with command and list of args (as strings).
 */
std::pair<Command*,std::list<std::string>> Parser::getNextCommand() {
  if (!isEnded()) { //check that there're more commands in the queue
    Command* tempCommand;
    std::list<std::string> tempList;

    //Check if the next command is function definition.
    if (*listIterator == "funcdef") {
      int steps = DefineFunction(listIterator);
      for (int i = 0; i < steps; i++) {
        listIterator++;
      }
    }


   //checking for matches in the commands map (that holds the known supported commands.
    auto mapIterator = commandMap.find(*listIterator); //find the right command
    if (mapIterator != commandMap.end()) {
      tempCommand = mapIterator->second; //save the command
        listIterator++;
      for (int i = 0; i < tempCommand->get_num_of_arg(); i++) { //get the arguments for the command
        tempList.emplace_back(*listIterator);
        listIterator++;
      }
      std::pair<Command*,std::list<std::string>> tempPair(tempCommand,tempList);
      return tempPair;

      //handles while and if loops: creating sub-list with the inside scope commands.
    } else if (*listIterator == "while" || *listIterator == "if") {
      std::string loopType = *listIterator;
      listIterator++;
      while (*listIterator != "{") {
        tempList.emplace_back(*listIterator);
        listIterator++;
      }
      tempList.emplace_back(*listIterator);
      listIterator++;

      //keep track of the number of brackets in order to support nested loops and ifs.
      int numberOfLeftBrackets = 1;
      int numberOfRightBrackets = 0;
      while (numberOfLeftBrackets > numberOfRightBrackets) {

        if (*listIterator == "}") {
          numberOfRightBrackets++;
          tempList.emplace_back(*listIterator);
        } else if (*listIterator == "{"){
          numberOfLeftBrackets++;
          tempList.emplace_back(*listIterator);
        } else {
          tempList.emplace_back(*listIterator);
        }
        listIterator++;
      }

      //create loop command, or if command.
      if (loopType == "while") {
        LoopCommand* loop_command = new LoopCommand(&tempList);
        conditionalCommands.emplace_back(loop_command);
        return std::pair<Command*,std::list<std::string>>(loop_command, tempList);
      } else if (loopType == "if") {
        IfCommand* if_command = new IfCommand(&tempList);
        conditionalCommands.emplace_back(if_command);
        return std::pair<Command*,std::list<std::string>>(if_command, tempList);
      }
    }
  }

  //default: if there's no such command, return a null command, that's how we know were done reading the code.
  NullCommand* null_command;
  listIterator++;
  return std::pair<Command*,std::list<std::string>>(null_command, std::list<std::string>());
}

/**
 * DefineFunction: define new function and add to the parser command's map.
 * @param iter iterator, pointing to the start of the function.
 * @return an integer the indicates how many steps the parser needs to stride.
 */
int Parser::DefineFunction(std::list<std::string>::iterator iter) {
  std::list<std::string> tempList;
  int steps = 0; //keeps track of the iterator strides.
  iter++; steps++;
  std::string funcName = *iter;

  while (*iter != "{") {
    tempList.emplace_back(*iter);
    iter++; steps++;
  }
  tempList.emplace_back(*iter);
  iter++; steps++;

  //keep track of the number of brackets in order to support nested loops and ifs inside the function.
  int numberOfLeftBrackets = 1;
  int numberOfRightBrackets = 0;
  while (numberOfLeftBrackets > numberOfRightBrackets) {

    if (*iter == "}") {
      numberOfRightBrackets++;
      tempList.emplace_back(*iter);
    } else if (*iter == "{"){
      numberOfLeftBrackets++;
      tempList.emplace_back(*iter);
    } else {
      tempList.emplace_back(*iter);
    }
    iter++; steps++;
  }
  FunctionCommand* function_command = new FunctionCommand(tempList);
  commandMap.insert({funcName, function_command}); //this function will now be recognized as valid command.
  return steps;
}

/**
 * check if there're more commands to perform
 * @return
 */
bool Parser::isEnded() {
  if (listIterator == commandList.end()) {
    return true;
  } else {
    return false;
  }
}
/**
 * Parser constructor
 * @param strList
 */
Parser::Parser(std::list<std::string> strList) {
  commandList = strList;
  listIterator = commandList.begin();

  //Add open server command to the map
  OpenServerCommand *ops = new OpenServerCommand();
  commandMap.insert({"openDataServer", ops});

  //Add open client command to the map
  connectControlClient* cnc = new connectControlClient();
  commandMap.insert({"connectControlClient", cnc});

  //Add assign var command to the map
  VarAssignCommand* vac = new VarAssignCommand();
  commandMap.insert({"=", vac});

  //Add define var command to the map
  DefineVarCommand* dvc = new DefineVarCommand();
  commandMap.insert({"simvar", dvc});

  //Add local var command to the map
  DefineLocalVarCommand* dlvc = new DefineLocalVarCommand();
  commandMap.insert({"var", dlvc});

  //Add print command to the map
  PrintCommand *print = new PrintCommand();
  commandMap.insert({"Print", print});

  //Add sleep command to the map
  SleepCommand *sleep = new SleepCommand();
  commandMap.insert({"Sleep", sleep});
}

//
// Created by ori294 on 12/19/19.
//

#include "ConditionParser.h"


ConditionParser::ConditionParser(std::list<std::string> strList) {
commandList = strList;
listIterator = commandList.begin();

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
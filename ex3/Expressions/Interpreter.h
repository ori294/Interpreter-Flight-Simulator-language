//
// Created by ori294 on 12/22/19.
//

#ifndef EX3_EXPRESSIONS_INTERPRETER_H_
#define EX3_EXPRESSIONS_INTERPRETER_H_
#include "Interpreter.h"
#include "Expression.h"
#include "ExpressionKinds.h"
#include <map>
#include <stack>
#include <queue>
#include <bits/stdc++.h>
#include <SimulatorManager.h>


using namespace std;

class Interpreter {
 private:
  map<string, double> variableMap;

 public:


  //useful methods, will be accessible without an instance of interpreter.
  static bool isDouble(string s);
  static bool isNegativeDouble(string s);
  Expression *shuntingCalculate(queue<string> expression);
  queue<string> ShuntingYard(vector<string> splitStr);
  vector<string> splitToArray(string str);
  void addOrNot(string checkStr);
  bool isWeakOperand(string op, stack<string> operators);
  void setVariables(string str);
  Expression *interpret(string str);
  Expression *change_var_to_value(string s);
};

#endif //EX3_EXPRESSIONS_INTERPRETER_H_
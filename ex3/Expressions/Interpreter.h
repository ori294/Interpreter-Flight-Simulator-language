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


using namespace std;

class Interpreter {
 private:
  map<string, double> variableMap;
  Expression* getPolishNotation(queue<string> RPN);

 public:
  Expression* interpret(string str);
  void setVariables(string str);

  //useful methods, will be accessible without an instance of interpreter.
  static bool isDouble(string s);
  static bool isNegativeDouble(string s);
};

#endif //EX3_EXPRESSIONS_INTERPRETER_H_

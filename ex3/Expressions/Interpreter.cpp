//
// Created by ori294 on 05/11/2019.
//

#include "Interpreter.h"

void Interpreter::setVariables(string str) {
  string s = str;
  string delimiter = ";";
  size_t pos = 0;
  string token;
  //cut the string by ';' and send to func addOrNot evey equation
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    addOrNot(token);
    s.erase(0, pos + delimiter.length());
  }
  //for case if the user input string without ";" in the end of the string//
  if (s.length() != 0) {
    token = s.substr(0, s.length());
    addOrNot(token);
  }
}

/*
 * interpret: a Shunting-yard algorithm for converting string into expression.
 * rules:
 * read the next ocject in the formula:
 * put vars and numbers in a queue
 * using stack and queue in order to change the order of the string to RPN,
 * a Reverse Polish Notation: https://en.wikipedia.org/wiki/Reverse_Polish_notation
 */
Expression *Interpreter::interpret(string str) {
  vector<string> splitStr = splitToArray(str);   //split the string to vector of strings
  queue<string> expression = ShuntingYard(splitStr); // make postfix presentation to the string
  Expression *exp = shuntingCalculate(expression); // make the Expression for return to the main
  return exp;
}
void Interpreter::addOrNot(string checkStr) {
  string s = checkStr;
  string delimiter = "=";
  size_t pos = s.find(delimiter);
  string tokenLeft = s.substr(0, pos); //left side of the string
  string tokenRight = s.substr(pos + 1); // right side
  regex re("(\\+|-)?[[:digit:]]+([.][[:digit:]]+)?");
  regex reVar("[a-zA-Z][0-9|A-Z|a-z|_]*");
  if (regex_match(tokenRight, re) && regex_match(tokenLeft, reVar)) { //check for number in the right side
    std::map<string, double>::iterator it = this->variableMap.find(tokenLeft);
    if (it != this->variableMap.end()) { //find maybe is update for some variables
      it->second = stod(tokenRight); //update the value
      return;
    }
    double value = stod(tokenRight);
    this->variableMap.insert(pair<string, double>(tokenLeft, value)); //insert new key and value
    return;
  }
  if (regex_match(tokenLeft, re)) { //check for number in the left side
    std::map<string, double>::iterator it = this->variableMap.find(tokenRight);
    if (it != this->variableMap.end()) { //find maybe is update for some variables
      it->second = stod(tokenLeft); //update the value
      return;
    }
    double value = stod(tokenLeft);
    this->variableMap.insert(pair<string, double>(tokenRight, value)); //insert new key and value
    return;
  }
  throw ("illegal variable assignment!"); //bad input trow exception
}

vector<string> Interpreter::splitToArray(string str) {
  vector<string> exp;
  size_t positionStart = 0;
  std::string token;
  int i(0);
  /*run all hte string and cut every part to vertebra in vector. this method full in conditions*/
  for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
    if (isdigit(str[i])) { //if the str[i] is digit
      std::string checkPoint = string(1, str[i]);
      char point = checkPoint[0];
      positionStart = i;
      while (isdigit(str[i]) || point == '.') { //scan whole the number
        ++i;
        checkPoint = string(1, str[i]);
        point = checkPoint[0];
      }
      token = str.substr(positionStart, i - positionStart);
      exp.push_back(token); //enter to the vector
      it = it + token.length() - 1; //update the place of iterator
      token.clear();
    } else {
      std::string checkOperand = string(1, str[i]);
      char operand = checkOperand[0];
      //find maybe the *it is operator
      if (operand == '*' || operand == '/' || operand == '-' || operand == '+' || operand == '(' || operand == ')') {
        exp.push_back(checkOperand);
        checkOperand.clear();
        ++i;
      } else {
        char under = str[i];
        if (isalpha(str[i]) || under == '_') { //when the str[i] is variable
          std::string searchName = string(1, str[i]);
          char search = searchName[0];
          size_t pos = i;
          //scan the whole name of the variable
          while (search != '*' && search != '+' && search != '/' && search != '-' && search != ')') {
            ++i;
            searchName = string(1, str[i]);
            search = searchName[0];
          }
          token = str.substr(pos, i - pos);
          auto value = this->variableMap.find(token); //find the value of this variable
          if (value->first.empty()) {
            throw ("error: un recognize expresion"); //invalid expresion
          }
          std::string number = to_string(value->second); //convert the value to string
          exp.push_back(number); //push the value in the vector
          it = it + token.length() - 1;
          token.clear();
        } else {
          throw ("error: invalid expresion"); //invalid expresion
        }
      }
    }
  }
  int flag = 0;
  for (auto ite = exp.begin(); ite != exp.end(); ++ite) {
    if (flag == 1 && *ite == *(ite - 1) && *ite != ")" && *ite != "(") {
      throw ("illegal math expression");
    }
    flag = 1;
  }
  return exp;
}

/* this method is boolean method , return if the operator weaker than the top operator in the stack*/
bool Interpreter::isWeakOperand(string op, stack<string> operators) {
  char o = op[0];
  bool YorN = false;
  switch (o) {
    case '(': break;
    case '+':
      try {
        if (operators.top() != "(") {
          YorN = true;
        }
      }
      catch (exception &e) {}
      break;
    case '-':
      try {
        if (operators.top() != "(") {
          YorN = true;

        }
      }
      catch (exception &e) {}
      break;
    case '*':
      try {

        if (!(operators.top() == "+" || operators.top() == "-" || operators.top() == "(" || operators.top() == "~"
            || operators.top() == "#")) {
        }
      }
      catch (exception &e) {}
      break;
    case '/':
      try {

        if (!(operators.top() == "+" || operators.top() == "-" || operators.top() == "(" || operators.top() == "~"
            || operators.top() == "#")) {
        }
      }
      catch (exception &e) {}
      break;
  }
  return YorN;
}

/*return the postfix presentation of the string we got in the main. the method work by the algorithm ShuntingYard*/
queue<string> Interpreter::ShuntingYard(vector<string> splitStr) {
  queue<string> VarAndOperator;
  stack<string> operators;
  regex re("(\\+|-)?[[:digit:]]+([.][[:digit:]]+)?");
  int flag = 1;
  for (auto it = splitStr.begin(); it != splitStr.end(); ++it) { //run on the vector
    if (regex_match(*it, re)) { //if its number
      VarAndOperator.emplace(*it);
    } else {
      if (*it == ")") { //pop all the operators until get "("
        while (operators.top() != "(") {
          string oP = operators.top();
          operators.pop();
          VarAndOperator.emplace(oP);
        }
        operators.pop();
      } else {
        if (!operators.empty() && isWeakOperand(*it, operators)) {
          while (!operators.empty() && isWeakOperand(*it, operators)) { //take out all the stronger operators
            string op = operators.top();
            operators.pop();
            VarAndOperator.emplace(op);
          }
          operators.push(*it);
        } else {
          if (*splitStr.begin() == "-" && flag == 1) { // - that is unary
            operators.push("~");
            flag = 0;
          } else {
            if (*splitStr.begin() == "+" && flag == 1) { // + that is unary
              operators.push("#");
              flag = 0;
            } else {
              if (*it == "-" && *(it - 1) == "(") { // + that is unary
                operators.push("~");
              } else {
                if (*it == "+" && *(it - 1) == "(") { // + that is unary
                  operators.push("#");
                } else {
                  operators.push(*it);
                }
              }
            }
          }
        }
      }
    }
  }
  while (!operators.empty()) { //in the end move all the operators to the queue
    string moving = operators.top();
    operators.pop();
    VarAndOperator.emplace(moving);
  }
  return VarAndOperator; //return queue
}

Expression *Interpreter::shuntingCalculate(queue<string> expression) { //make the Expression
  stack<Expression *> final;
  regex re("(\\+|-)?[[:digit:]]+([.][[:digit:]]+)?");
  while (!expression.empty()) {
    if (regex_match(expression.front(), re)) {
      final.push(new Value(stod(expression.front())));
      expression.pop();
      continue;
    }
    if (expression.front() == "~") {
      Expression *tmp = final.top();
      final.pop();
      final.push(new UMinus(tmp));
      expression.pop();
      continue;
    }
    if (expression.front() == "#") {
      Expression *tmp = final.top();
      final.pop();
      final.push(new UPlus(tmp));
      expression.pop();
      continue;
    }
    if (expression.front() == "+") {
      Expression *tmpRight = final.top();
      final.pop();
      if (!final.empty()) {
        Expression *tempLeft = final.top();
        final.pop();
        final.push(new Plus(tempLeft, tmpRight));
        expression.pop();
      } else {
        throw ("illegal math expression");
      }

      continue;
    }
    if (expression.front() == "-") {
      Expression *tmpRight = final.top();
      final.pop();
      if (!final.empty()) {
        Expression *tempLeft = final.top();
        final.pop();
        final.push(new Minus(tempLeft, tmpRight));
        expression.pop();
      } else {
        throw ("illegal math expression");
      }

      continue;
    }
    if (expression.front() == "*") {
      Expression *tmpRight = final.top();
      final.pop();
      if (!final.empty()) {
        Expression *tempLeft = final.top();
        final.pop();
        final.push(new Mul(tempLeft, tmpRight));
        expression.pop();
      } else {
        throw ("illegal math expression");
      }
      continue;
    }
    if (expression.front() == "/") {
      Expression *tmpRight = final.top();
      final.pop();
      if (!final.empty()) {
        Expression *tempLeft = final.top();
        final.pop();
        final.push(new Div(tempLeft, tmpRight));
        expression.pop();
      } else {
        throw ("illegal math expression");
      }
      continue;
    }
  }
  return final.top();
}

/*
 * isDouble: given a string, check if it's a double.
 */
bool Interpreter::isDouble(string s) {
  return std::regex_match(s, std::regex("[0-9.]+"));
}

/*
 * isNegativeDouble: given a string, check if it's a negative double.
 */
bool Interpreter::isNegativeDouble(string s) {
  return std::regex_match(s, std::regex("[-0-9.]+"));
}
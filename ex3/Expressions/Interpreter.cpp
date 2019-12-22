//
// Created by ori294 on 05/11/2019.
//

#include "Interpreter.h"

/*
 * interpret: a Shunting-yard algorithm for converting string into expression.
 * rules:
 * read the next ocject in the formula:
 * put vars and numbers in a queue
 * using stack and queue in order to change the order of the string to RPN,
 * a Reverse Polish Notation: https://en.wikipedia.org/wiki/Reverse_Polish_notation
 */
Expression* Interpreter::interpret(string str) {
  vector<string> RPN; //Reverse Polish Notation.
  stack<string> operandStack; //will manipulate operands during the algorithm
  queue<string> variablesQueue; //will manipulate the variables
  map<string, double>::iterator iterator;

  bool isPrevNum = false; //did we read a number / variable in the last iteration.

  //main loop - for each char in string
  for (int i = 0; i < str.length(); ) {
    if (isDouble(string(1, str[i]))) {
      isPrevNum = true;
      string temp;
      //found a number, read all digits and bind them together
      while (isDouble(string(1, str[i]))) {
        temp += str[i];
        i++;
      }
      RPN.push_back(temp);
    } else {
      if (str[i] == char('+') && isPrevNum) {
        RPN.push_back("Plus");
        isPrevNum = false;
      } else if(str[i] == char('+') && !isPrevNum) { //it means we read unary plus
        RPN.push_back("UPlus");
        isPrevNum = false;
      } else if(str[i] == char('-') && isPrevNum) {
        RPN.push_back("Minus");
        isPrevNum = false;
      } else if(str[i] == char('-') && !isPrevNum) { //it means we read unary minus
        RPN.push_back("UMinus");
        isPrevNum = false;
      } else if(str[i] == char('*') && isPrevNum) {
        RPN.push_back("Mul");
        isPrevNum = false;
      } else if(str[i] == char('/') && isPrevNum) {
        RPN.push_back("Div");
        isPrevNum = false;
      } else if(str[i] == char(')')) {
        RPN.push_back("RB"); //stands for right bracket"
        isPrevNum = true;
      } else if(str[i] == char('(')) {
        RPN.push_back("LB"); //stands for left bracket
        isPrevNum = false;

        //a case for variables.
      } else if (std::regex_match(string(1, str[i]), std::regex("[a-zA-z]"))) {
        string temp = string(1, str[i]);
        while (string(1, str[i+1]) == "_" ||
            std::regex_match(string(1, str[i+1]), std::regex("[0-9]"))) {
          temp += str[++i];
        }
        RPN.push_back(temp);
        isPrevNum = true;
        //invalid char
      } else {
        throw "illegal math expression";
      }
      i++;
    }
  }

  //second part of the algorithm, order vars and operands in reverse polish notation.
  for (std::vector<string>::iterator it = RPN.begin(); it != RPN.end(); ++it) {
    if (isDouble(*it)) {
      variablesQueue.push(*it); //number - just push to queue

    } else if (string("Mul") == (*it) || string("Div") == (*it)) {
      //higher order operands when stack is empty
      if (operandStack.empty()) {
        operandStack.push(*it);

      } else if (string("Mul") == (operandStack.top()) || string("Div") == (operandStack.top())){
        //higher order operands when there's another higher order operand before it
        variablesQueue.push(operandStack.top());
        operandStack.pop();
        operandStack.push(*it);

        //higher order operands when there's lower order operand before it
      } else {
        operandStack.push(*it);
      }
    } else if (string("Plus") ==  (*it) || string("Minus") == (*it)) {
      //lower order operands when stack is empty
      if(operandStack.empty()) {
        operandStack.push(*it);

        //the only lower operand is left bracket
      } else if (string("LB") == (operandStack.top())) {
        operandStack.push(*it);

        //when there's higher order operand in stack
      } else {
        variablesQueue.push(operandStack.top());
        operandStack.pop();
        operandStack.push(*it);
      }

    } else if (string("UMinus") == (*it) || string("UPlus") == (*it)) {
      //lower order operands when stack is empty
      if(operandStack.empty()) {
        operandStack.push(*it);

        //the only lower operand is left bracket
      } else if (string("LB") == (operandStack.top())) {
        operandStack.push(*it);

        //when there's higher order operand in stack
      } else {
        variablesQueue.push(operandStack.top());
        operandStack.pop();
        operandStack.push(*it);
      }

      //left bracket - just push
    } else if(string("LB") == (*it)) {
      operandStack.push(*it);

      //empty stack to the queue until the closing right bracket
    } else if(string("RB") == (*it)) {
      while (!operandStack.empty()) {
        if (operandStack.top() != ("LB")) {
          variablesQueue.push(operandStack.top());
          operandStack.pop();
        } else {
          operandStack.pop(); //delete the right bracket
          break;
        }
      }

      //anything else - variables
    } else {
      variablesQueue.push(*it);
    }
  }

  //when done reading, empty stack into the queue.
  while (!operandStack.empty()) {
    variablesQueue.push(operandStack.top());
    operandStack.pop();
  }

  //build an Expression out of the Revere Polish Notation.
  Expression* interpretation = getPolishNotation(variablesQueue);
  return interpretation;
}

/*
 * getPolishNotation: given a RPN string, return the expression using stack.
 */
Expression* Interpreter::getPolishNotation(queue<string> RPN) {
  stack<Expression*> valueStack;

  //main loop - read the RPN string, represented by queue.
  while (!RPN.empty()) {
    //unary plus - bind operand and last var, than push back to stack
    if (RPN.front() == "UPlus") {
      Expression* up = new UPlus(valueStack.top());
      valueStack.pop();
      valueStack.push(up);

      //unary minus - bind operand and last var, than push back to stack
    } else if (RPN.front() == "UMinus") {
      Expression* up = new UMinus(valueStack.top());
      valueStack.pop();
      valueStack.push(up);

      //plus - bind operand and two last vars, than push back to stack
    } else if (RPN.front() == "Plus") {
      Expression* x = valueStack.top();
      valueStack.pop();
      Expression* y = valueStack.top();
      valueStack.pop();
      Expression* plus = new Plus(y, x);
      valueStack.push(plus);

      //minus - bind operand and two last vars, than push back to stack
    } else if (RPN.front() == "Minus") {
      Expression* x = valueStack.top();
      valueStack.pop();
      Expression* y = valueStack.top();
      valueStack.pop();
      Expression* minus = new Minus(y, x);
      valueStack.push(minus);

      //Multipy - bind operand and two last vars, than push back to stack
    } else if (RPN.front() == "Mul") {
      Expression* x = valueStack.top();
      valueStack.pop();
      Expression* y = valueStack.top();
      valueStack.pop();
      Expression* mul = new Mul(y, x);
      valueStack.push(mul);

      //Divide - bind operand and two last vars, than push back to stack
    } else if (RPN.front() == "Div") {
      Expression* x = valueStack.top();
      valueStack.pop();
      Expression* y = valueStack.top();
      valueStack.pop();
      Expression* div = new Div(y, x);
      valueStack.push(div);

      //When the object is a number (double).
    } else if (isDouble(RPN.front())) {
      Expression* val = new Value(stod(RPN.front()));
      valueStack.push(val);

      //When the object is a variable, assign a value from the map.
    } else {
      Expression* var = new Variable(RPN.front(), variableMap.find(RPN.front())->second);
      valueStack.push(var);
    }
    RPN.pop();
  }

  //check that the algorithm read everything, raise error if not.
  if (valueStack.size() > 1) {
    throw "illegal math expression";
  }
  return valueStack.top();
}

/*
 * setVariables: given a string, set a map with values and strings
 */
void Interpreter::setVariables(string str) {

  //agreed format for spliting two assignments in one string.
  char delimiter(';');
  queue<char> charQueue;
  vector<string> assignments;
  int delimFound = 0;

  //find delimiter and split the string
  for (int i = 0; i <= str.length(); i++) {
    if (str[i] != delimiter && str[i] != '\0') {
      charQueue.push(str[i]);

    }else if (str[i] == delimiter || str[i] == '\0') {
      string temp;
      while (!charQueue.empty()) {
        temp += charQueue.front();
        charQueue.pop();
      }
      delimFound++;
      assignments.push_back(temp);
    }
  }

  //if there's no delimiter, it means we got only one assignment
  if(!delimFound) {
    assignments.push_back(str);
  }

  //after splitting the string into assignments, iterate:
  for (std::vector<string>::iterator it = assignments.begin() ; it != assignments.end(); ++it) {
    //divide the string with '=', accepting reverse assignment too (value = string)
    string leftArg = it->substr(0, it->find('='));
    string rightArg = it->substr(it->find('=') + 1, it->length() - it->find('='));


    //check if right side is a double, or a negative double.
    if (isDouble(rightArg) || isNegativeDouble(rightArg)) {

      //check if the var is already assigned, if it is, only change it's value.
      if(variableMap.find(leftArg) == variableMap.end()) {
        variableMap.insert(pair<string, double>(leftArg, stod(rightArg)));
      } else {
        variableMap.find(leftArg)->second = stod(rightArg);
      }

      //check if the var is already assigned, if it is, only change it's value.
    } else if (isDouble(leftArg) || isNegativeDouble(leftArg)) {
      if (variableMap.find(rightArg) == variableMap.end()) {
        variableMap.insert(pair<string, double>(rightArg, stod(leftArg)));
      } else {
        variableMap.find(rightArg)->second = stod(leftArg);
      }

      //Raise an error when ever there's no number in the assignment.
    } else {
      throw "illegal variable assignment!";
    }
  }
}

/*
 * isDouble: given a string, check if it's a double.
 */
bool Interpreter::isDouble(string s){
  return std::regex_match(s, std::regex("[0-9.]+"));
}

/*
 * isNegativeDouble: given a string, check if it's a negative double.
 */
bool Interpreter::isNegativeDouble(string s){
  return std::regex_match(s, std::regex("[-0-9.]+"));
}
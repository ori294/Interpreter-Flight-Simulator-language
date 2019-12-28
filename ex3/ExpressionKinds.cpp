//
// Created by ori294 on 12/17/19.
//

#include "ExpressionKinds.h"

//Variable methods:
//Constructor
Variable::Variable(string name, double number) {
  this->varName = name;
  Value *val = new Value(number);
  this->value = val;
}
//Calculate
double Variable::calculate(){return this->value->calculate();}
string Variable::getVarName() {return this->varName;}
double Variable::getValue() {return this->value->calculate();}
void Variable::setVarValue(double val) {this->value->setValue(val);}

//Operators overloading:
Variable& Variable::operator +=(Variable x) {
  this->setVarValue(this->getValue() + x.getValue());
  return *this;
}
Variable& Variable::operator -=(Variable x) {
  this->setVarValue(this->getValue() - x.getValue());
  return *this;
}
Variable& Variable::operator += (double x) {
  this->setVarValue(this->getValue() + x);
  return *this;
}
Variable& Variable::operator -= (double x) {
  this->setVarValue(this->getValue() - x);
  return *this;
}
Variable& Variable::operator ++ (int) {
  this->setVarValue(this->getValue() + 1);
  return *this;
}
Variable& Variable::operator -- (int) {
  this->setVarValue(this->getValue() - 1);
  return *this;
}
Variable& Variable::operator ++ () {
  this->setVarValue(this->getValue() + 1);
  return *this;
}
Variable& Variable::operator -- () {
  this->setVarValue(this->getValue() - 1);
  return *this;
}


//Destructor
Variable::~Variable() {
  delete this->value;
  //delete this;
}

//Value methods
//Constructor
Value::Value(double value) : exValue(value) {}
//Calculate
double Value::calculate(){return this->exValue;}
void Value::setValue(double newVal) {this->exValue = newVal;}
//Destructor
Value::~Value() {}

//BinaryOperator methods
//Constructor - assign left and right Expressions.
BinaryOperator::BinaryOperator(Expression &left, Expression &right) : leftEx(&left), rightEx(&right) {}
//Calculate
double BinaryOperator::calculate() {return 0;}
//Destructor - delete left and right Expressions.
BinaryOperator::~BinaryOperator() {}

//Plus methods
//Constructor
Plus::Plus( Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Plus::calculate() {return (leftEx->calculate() + rightEx->calculate());}
//Destructor
Plus::~Plus() {
  delete(leftEx);
  delete(rightEx);
}


//Minus methods
//Constructor
Minus::Minus(Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Minus::calculate() {return (leftEx->calculate() - rightEx->calculate());}
//Destructor
Minus::~Minus() {
  delete(leftEx);
  delete(rightEx);
  //delete this;
}


//Mul methods
//Constructor
Mul::Mul(Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Mul::calculate() {return (leftEx->calculate() * rightEx->calculate());}
//Destructor
Mul::~Mul() {
  delete(leftEx);
  delete(rightEx);
  //delete this;
}


//Div methods
//Constructor
Div::Div( Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Div::calculate() {
  double rgt = rightEx->calculate();
  if (rgt == 0) {
    throw "division by zero";
  }
  return (leftEx->calculate() / rightEx->calculate());
}
//Destructor
Div::~Div() {
  delete(leftEx);
  delete(rightEx);
  //delete this;
}

//BooleanOperator methods
//Constructor - assign left and right Expressions.
BooleanOperator::BooleanOperator(Expression *left,std::string con , Expression *right)
: leftEx(left), rightEx(right) {
  this->Condition = con;
}
//Calculate
double BooleanOperator::calculate() {
  double leftVal = leftEx->calculate();
  double rightVal = rightEx->calculate();

  double value = 0;
  if (this->Condition == "==") {
    leftVal == rightVal ? value = 1 : value = 0;
  } else if (this->Condition == "!=") {
    leftVal != rightVal ? value = 1 : value = 0;
  } else if (this->Condition == ">") {
    leftVal > rightVal ? value = 1 : value = 0;
  } else if (this->Condition == "<") {
    leftVal < rightVal ? value = 1 : value = 0;
  } else if (this->Condition == "<=") {
    leftVal <= rightVal ? value = 1 : value = 0;
  } else if (this->Condition == ">=") {
    leftVal >= rightVal ? value = 1 : value = 0;
  }
  return value;
}
//Destructor - delete left and right Expressions.
BooleanOperator::~BooleanOperator() {
  delete(leftEx);
  delete(rightEx);
}

//UnaryOperator methods
//Constructor
UnaryOperator::UnaryOperator(Expression &expression) : expressionA(&expression) {}
//Calculate
double UnaryOperator::calculate() {return 0;}
//Destructor
UnaryOperator::~UnaryOperator() {}

//UPlus methods
//Constructor
UPlus::UPlus(Expression *expression) : UnaryOperator(*expression) {}
//Calculate
double UPlus::calculate() {return expressionA->calculate();}
//Destructor
UPlus::~UPlus() {
  delete(expressionA);
  //delete this;
}

//UMinus methods
//Constructor
UMinus::UMinus(Expression *expression) : UnaryOperator(*expression) {}
//Calculate
double UMinus::calculate() {return (-1 * expressionA->calculate());}
//Destructor
UMinus::~UMinus() {
  delete(expressionA);
  //delete this;
}
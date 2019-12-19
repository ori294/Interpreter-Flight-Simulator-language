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
Variable& Variable::operator ++ (int dummy) {
  this->setVarValue(this->getValue() + 1);
  return *this;
}
Variable& Variable::operator -- (int dummy) {
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
Value::Value(double value) : value(value) {}
//Calculate
double Value::calculate(){return this->value;}
void Value::setValue(double newVal) {this->value = newVal;}
//Destructor
Value::~Value() {}

//BinaryOperator methods
//Constructor - assign left and right Expressions.
BinaryOperator::BinaryOperator(Expression &left, Expression &right) : left(&left), right(&right) {}
//Calculate
double BinaryOperator::calculate() {}
//Destructor - delete left and right Expressions.
BinaryOperator::~BinaryOperator() {}

//Plus methods
//Constructor
Plus::Plus( Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Plus::calculate() {return (left->calculate() + right->calculate());}
//Destructor
Plus::~Plus() {
  delete(left);
  delete(right);
}


//Minus methods
//Constructor
Minus::Minus(Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Minus::calculate() {return (left->calculate() - right->calculate());}
//Destructor
Minus::~Minus() {
  delete(left);
  delete(right);
  //delete this;
}


//Mul methods
//Constructor
Mul::Mul(Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Mul::calculate() {return (left->calculate() * right->calculate());}
//Destructor
Mul::~Mul() {
  delete(left);
  delete(right);
  //delete this;
}


//Div methods
//Constructor
Div::Div( Expression *left, Expression *right) : BinaryOperator(*left, *right) {}
//Calculate
double Div::calculate() {
  double rgt = right->calculate();
  if (rgt == 0) {
    throw "division by zero";
  }
  return (left->calculate() / right->calculate());
}
//Destructor
Div::~Div() {
  delete(left);
  delete(right);
  //delete this;
}

//BooleanOperator methods
//Constructor - assign left and right Expressions.
BooleanOperator::BooleanOperator(Expression &left,std::string con , Expression &right)
: left(&left), right(&right) {
  this->Condition = con;
}
//Calculate
double BooleanOperator::calculate() {
  double leftVal = left->calculate();
  double rightVal = right->calculate();

  if (this->Condition == "==") {
    leftVal == rightVal ? 1 : 0;
  } else if (this->Condition == "!=") {
    leftVal != rightVal ? 1 : 0;
  } else if (this->Condition == ">") {
    leftVal > rightVal ? 1 : 0;
  } else if (this->Condition == "<") {
    leftVal < rightVal ? 1 : 0;
  } else if (this->Condition == "<=") {
    leftVal <= rightVal ? 1 : 0;
  } else if (this->Condition == ">=") {
    leftVal >= rightVal ? 1 : 0;
  }
}
//Destructor - delete left and right Expressions.
BooleanOperator::~BooleanOperator() {
  delete(left);
  delete(right);
}

//UnaryOperator methods
//Constructor
UnaryOperator::UnaryOperator(Expression &expression) : expression(&expression) {}
//Calculate
double UnaryOperator::calculate() {}
//Destructor
UnaryOperator::~UnaryOperator() {}

//UPlus methods
//Constructor
UPlus::UPlus(Expression *expression) : UnaryOperator(*expression) {}
//Calculate
double UPlus::calculate() {return expression->calculate();}
//Destructor
UPlus::~UPlus() {
  delete(expression);
  //delete this;
}


//UMinus methods
//Constructor
UMinus::UMinus(Expression *expression) : UnaryOperator(*expression) {}
//Calculate
double UMinus::calculate() {return (-1 * expression->calculate());}
//Destructor
UMinus::~UMinus() {
  delete(expression);
  //delete this;
}
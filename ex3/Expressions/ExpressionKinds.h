//
// Created by ori294 on 12/17/19.
//

#ifndef EX3_EXPRESSIONS_EXPRESSIONKINDS_H_
#define EX3_EXPRESSIONS_EXPRESSIONKINDS_H_
#include "Expression.h"
#include "stdio.h"
#include "string"


using namespace std;

//Value class
class Value : virtual public Expression {
 private:
  double value;

 public:
  Value(double value);
  double calculate() override ;
  ~Value();
  void setValue(double newVal);
};

//Variable class
class Variable : virtual public Expression {
 private:
  string varName;
  Value *value;

 public:
  Variable(string name, double value);
  double calculate() override ;
  void setVarValue(double val);
  double getValue();
  string getVarName();
  Variable& operator += (const Variable x);
  Variable& operator -= (const Variable x);
  Variable& operator += (double x);
  Variable& operator -= (double x);
  Variable& operator ++ (int dummy); //post-fix ++
  Variable& operator -- (int dummy); //post-fix --
  Variable& operator ++ (); //pre-fix ++
  Variable& operator -- (); //pre-fix --
  ~Variable();
};

//BinaryOperator class
class BinaryOperator : virtual public Expression {
 protected:
  Expression *left;
  Expression *right;

 public:
  BinaryOperator(Expression &left, Expression &right);
  double calculate () override;
  void setValue(double val);
  virtual ~BinaryOperator();
};

//Plus class
class Plus : virtual public BinaryOperator {

 public:
  Plus(Expression *left, Expression *right);
  double calculate () override;
  ~Plus();
};

//Minus class
class Minus : virtual public BinaryOperator {

 public:
  Minus(Expression *left, Expression *right);
  double calculate () override;
  ~Minus();
};

//Mul class
class Mul : virtual public BinaryOperator {

 public:
  Mul(Expression *left, Expression *right);
  double calculate () override;
  ~Mul();
};

//Div class
class Div : virtual public BinaryOperator {

 public:
  Div(Expression *left, Expression *right);
  double calculate () override;
  ~Div();
};


//UnaryOperator class
class UnaryOperator : virtual public Expression {
 protected:
  Expression *expression;

 public:
  UnaryOperator(Expression &expression);
  double calculate () override;
  virtual ~UnaryOperator();
};

//UPlus class
class UPlus : virtual public UnaryOperator {

 public:
  UPlus(Expression *expression);
  double calculate () override;
  ~UPlus();
};

//UMinus class
class UMinus : virtual public UnaryOperator {

 public:
  UMinus(Expression *expression);
  double calculate () override;
  ~UMinus();
};

#endif //EX3_EXPRESSIONS_EXPRESSIONKINDS_H_

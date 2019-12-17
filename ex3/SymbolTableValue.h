//
// Created by ori294 on 12/17/19.
//

#ifndef EX3__SYMBOLTABLEVALUE_H_
#define EX3__SYMBOLTABLEVALUE_H_
#include "Expressions/ExpressionKinds.h"

class SymbolTableValue {
 private:
  Expression* exp;
  std::string simAdress;
  bool RightBinded;

 public:
  SymbolTableValue(Expression* expression, std::string sim, bool directionIsRight) {
    this->exp = expression;
    this->simAdress = sim;
    this->RightBinded = directionIsRight;
  }

  Expression* getExpression() {
    return this->exp;
  }

  Expression* setValue(float value) {
    delete this->exp;
    this->exp = new Value(value);
  }
};

#endif //EX3__SYMBOLTABLEVALUE_H_

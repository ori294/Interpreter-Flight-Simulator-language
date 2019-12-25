//
// Created by ori294 on 12/17/19.
//

#ifndef EX3__SYMBOLTABLEVALUE_H_
#define EX3__SYMBOLTABLEVALUE_H_
#include "ExpressionKinds.h"

/**
 * SymbolTable value - holds the data needed in one object.
 */
class SymbolTableValue {
 private:
  Expression* exp;
  std::string simAdress;
  bool RightBinded;

 public:
  /**
   * Symbol Table Value CTOR.
   * @param expression a mathematical expression.
   * @param sim var adress inside the simulator.
   * @param directionIsRight bool value, will be true if and only if the bind direction is right.
   */
  SymbolTableValue(Expression* expression, std::string sim, bool directionIsRight) {
    this->exp = expression;
    this->simAdress = sim;
    this->RightBinded = directionIsRight;
  }

  /**
   * return the expression
   * @return an expression
   */
  Expression* getExpression() {
    return this->exp;
  }

  /**
   * replace the expression.
   * @param value new float value
   */
  void setValue(float value) {
    if (this->exp != nullptr) {
      delete this->exp;
      this->exp = new Value(value);
    }
  }
  std::string getSimAddress() {return this->simAdress;}

  bool getBind() {return this->RightBinded;}

  /**
   * symbol value DTOR.
   */
  ~SymbolTableValue() {delete this->exp;}
};

#endif //EX3__SYMBOLTABLEVALUE_H_

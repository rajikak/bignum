#ifndef AST_H
#define AST_H

#include "bignum.h"

using namespace std;

class AST;
class Expression;
class BinaryOp;
class UnaryOp;

class ASTVisitor {
	public:
		virtual void visit(AST &) {};
		virtual void visit(Expression &) = 0;
		virtual void visit(UnaryOp &) = 0;
		virtual void visit(BinaryOp &) = 0;
};

class AST {
	public:
		virtual ~AST() {}
		virtual void accept(ASTVisitor &V) = 0;
};


class Expression: public AST {
	public:
		Expression() {}
};

class Statment: public Expression {
	Expression *E;

	public:
		Statment(Expression *E): E(E) {}
		Expression *getExpression() { return E; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

class BinaryOp : public Expression {
	public:
		enum BinOp {Plus, Minus, Mul, Div, Pow, Exp, Rho, Itoa};
	private:
		Expression *Left;
		Expression *Right;
		BinOp Op;

	public:
		BinaryOp(BinOp Op, Expression *L, Expression *R): Op(Op), Left(L), Right(R) {}
		Expression *getLeft() { return Left; }
		Expression *getRight() {return Right; }
		BinOp getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

class UnaryOp: public Expression {
	public:
		enum UnOp {Itoa, Rand/*(?)*/};
	private:
		Expression *Operand;
		UnOp Op;

	public:
		UnaryOp(UnOp Op, Expression *E): Op(Op), Operand(E) {}
		Expression *getOperand() { return Operand; }
		UnOp getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

#endif

#ifndef AST_H
#define AST_H

#include "bignum.h"

class AST;
class Program;
class Statment;
class Expression;
class BinaryOperator;
class UnaryOperator;

class ASTVisitor {
	public:
		virtual void visit(AST &) {};
		virtual void visit(Program &) = 0;
		virtual void visit(Statment &) = 0;
		virtual void visit(Expression &) = 0;
		virtual void visit(BinaryOperator &) = 0;
		virtual void visit(UnaryOperator &) = 0;
};

class AST {
	public:
		virtual ~AST() {}
		virtual void accept(ASTVisitor &V) = 0;
};

class Program: public AST {
	private:
		vector<Statment> Stmts;
	public:
		Program(vector<Statment> Stmts) {
			Stmts = Stmts;
		}
};

class Expression: public Expr {
	pulic:
		Expression() {}
};

class Statment: public Expression {};

class BinaryOperator : public Expression {
	public:
		enum BinOp {Plus, Minus, Mul, Div, Pow, Exp, Rho, Itoa};
	private:
		Expression *Left;
		Expression *Right;
		BinOp Op;

	public:
		BinaryOperator(BinOp Op, Expression *L, Expression *R): Op(Op), Left(L), Right(R) {}
		Expression *getLeft() { return Left; }
		Expression *getRight() {return Right; }
		BinOp getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

class UnaryOperator: public Expression {
	public:
		enum UnOp {Itoa, Rand};
	private:
		Expression *Operand;
		UnOp Op;

	public:
		UnaryOperator(UnOp Op, Expression *R): Op(Op), Right(R) {}
		Expression getOperand() { return Operand; }
		UnOp getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

#endif

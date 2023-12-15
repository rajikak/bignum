#ifndef AST_H
#define AST_H

#include "bignum.h"

using namespace std;

class AST;
class Expression;
class Factor;
class BinaryOp;
class UnaryOp;

class ASTVisitor {
	public:
		virtual void visit(AST &) {};
		virtual void visit(Expression &) = 0;
		virtual void visit(Factor &) = 0;
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

class Factor: public Expression {
	public:
		enum ValueKind {Number};
	private:
		ValueKind Kind;
		llvm::StringRef Val;

	public:
		Factor(ValueKind Kind, llvm::StringRef Val): Kind(Kind), Val(Val){}
		ValueKind getKind() { return Kind; };
		llvm::StringRef getVal() { return Val; };
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

class BinaryOp : public Expression {
	public:
		enum Operator {Plus, Minus, Mul, Div, Pow, Exp, Rho, Itoa};
	private:
		Expression *Left;
		Expression *Right;
		Operator Op;

	public:
		BinaryOp(Operator Op, Expression *L, Expression *R): Op(Op), Left(L), Right(R) {}
		Expression *getLeft() { return Left; }
		Expression *getRight() {return Right; }
		Operator getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

class UnaryOp: public Expression {
	public:
		enum Operator {Itoa, Rand/*(?)*/};
	private:
		Expression *Operand;
		Operator Op;

	public:
		UnaryOp(Operator Op, Expression *E): Op(Op), Operand(E) {}
		Expression *getOperand() { return Operand; }
		Operator getOperator() { return Op; }
		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};

#endif

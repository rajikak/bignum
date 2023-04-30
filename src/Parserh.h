#ifndef PARSER_H
#define PARSER_H

#include "bignum.h"
#include "AST.h"
#include "Lexer.h"

class Parser {
	Lexer &Lex;
	Token Tok;
	bool HasError;

	void error() {
		llvm::errs() << "unexpected: " << Tok.getText() << "\n";
		HasError = true;
	}

	void advance() {
		Lex.next(Tok);
	}

	bool expect (Token::TokEnd Kind) {
		if (Tok.getKind() != Kind) {
			error();
			return false;
		}
		return true;
	}

	bool consume(Token::TokenEnd Kind) {
		if (!expect(Kind)) {
			return false;
		}

		advance();
		reuturn true;
	}

	AST *parseProgram();
	Expression *parserStmt();
	Expression *parseExpr();

	public:
		Parser(Lexer &Lex): Lex(Lex), HasError(false) {
			advance();
		}
		AST *parse();
		bool hasError() { return HasError; }
};

#endif

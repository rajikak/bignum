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
		llvm::errs() << "unexpected: " << Tok.getLiteral() << "\n";
		HasError = true;
	}

	void advance() {
		Lex.nextToken(Tok);
	}

	bool expect (Token::TokenKind Kind) {
		if (Tok.getKind() != Kind) {
			error();
			return false;
		}
		return true;
	}

	bool consume(Token::TokenKind Kind) {
		if (!expect(Kind)) {
			return false;
		}

		advance();
		return true;
	}

	AST *parseCalc();
	Expression *parseExpr();
	Expression *parseTerm();
	Expression *parseFactor();

	public:
		Parser(Lexer &Lex): Lex(Lex), HasError(false) {
			advance();
		}
		AST *parse();
		bool hasError() { return HasError; }
};

#endif

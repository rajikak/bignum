#ifndef LEXER_H
#define LEXER_H

#include "bignum.h"

using namespace std;

class Lexer;

class Token {
	friend class Lexer;

public:
	enum TokenKind : unsigned short {
		ILLEGAL,
		EOI,
		COMMENT,
	
		PLUS,
		MINUS,
		ASTERRISK,
		SLASH,
		POWER, // **
		RANDOM,
		
		LPARAN,
		RPARAN,

		NUMBER,
		E,
		ITOA,
		RHO,
	};

private:
	TokenKind Kind;
	llvm::StringRef Literal;

public:
	TokenKind getKind() const { return Kind; }
	llvm::StringRef getLiteral() const { return Literal; }
	bool is(TokenKind K) const { return Kind == K; }
	bool isOneOf(TokenKind K1, TokenKind K2) const { return is(K1) || is(K2); }
	template <typename... Ts>
	bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
		return is(K1) || isOneOf(K2, Ks...);
	}
};

class Lexer {

private:
	const char *BufferStart; // input buffer is a C string ('\0')
	const char *BufferPtr;

	Token::TokenKind lookupLongOperator(llvm::StringRef ident);
	void newToken(Token &Tok, const char *TokEnd, Token::TokenKind Kind);

public:
	Lexer(const llvm::StringRef &Buffer) {
		BufferStart = Buffer.begin();
		BufferPtr = BufferStart;
	}

	void nextToken(Token &Tok);
	void printToken(Token Tok);
};

#endif

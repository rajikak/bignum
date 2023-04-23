#ifndef LEXER_H
#define LEXER_H

#include "bignum.h"

using namespace std;

class Lexer;

class Token {
	friend class Lexer;

public:
	enum TokenType : unsigned short {
		ILLEGAL,
		EOI,
		COMMENT,
	
		PLUS,
		MINUS,
		ASTERRISK,
		SLASH,
		
		LPARAN,
		RPARAN,
	};

private:
	TokenType Type;
	llvm::StringRef Literal;

public:
	TokenType getType() const { return Type; }
	llvm::StringRef getLiteral() const { return Literal; }
	bool is(TokenType T) const { return Type == T; }
	book isOneOf(TokenType T1, TokenType T2) const { return is(T1) || is(T2); }
	template <typename... Ts>
	bool isOneOf(TokenType T1, TokenType T2, Ts... Ks) const {
		return is(T1) || isOneOf(T2, Ks...);
	}
};

class Lexer {

private:
	const char *BufferStart; // input buffer is a C string ('\0')
	const char *BufferPtr;

	Token::TokenType lookupIdent(llvm::StringRef ident);
	void newToken(Token &Tok, const char *TokEnd, Token::TokenType TokenType);

public:
	Lexer(const llvm::StringRef &Buffer) {
		BufferStart = Buffer.begin();
		BufferPtr = BufferStart;
	}

	void nextToken(Token &Tok);
	void printToken(Token Tok);
};

#endif

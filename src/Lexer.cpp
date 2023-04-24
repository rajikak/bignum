#include "bignum.h"
#include "Lexer.h"

using namespace std;

namespace charinfo {
LLVM_READNONE inline bool isWhiteSpace(char c) {
	return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' ||
		   c == '\n' || c == '\b';
}

LLVM_READNONE inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

LLVM_READNONE inline bool isLetter(char c) { 
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

LLVM_READNONE inline bool isAlphaNumeric(char c) {
	return isDigit(c) || isLetter(c);
}
} //namespace charinfo


void Lexer::printToken(Token Tok) {
	map<Token::TokenType, string> m{
			{Token::ILLEGAL, "illegal token"},
			{Token::EOI, "end of input"},
			{Token::PLUS, "operator"},
			{Token::MINUS, "operator"},
			{Token::ASTERRISK, "operator"},
			{Token::POWER, "operator"},
			{Token::SLASH, "operator"},
			{Token::E, "operator"},
			{Token::ITOA, "operator"},
			{Token::RHO, "operator"},
			{Token::NUMBER, "number"},
			{Token::RANDOM, "operator"}
	};

	cout << "[" << Tok.getLiteral().str() << "," << m[Tok.getType()] << "]" << endl;
}

Token::TokenType Lexer::lookupLongOperator(llvm::StringRef op) {
	map<string, Token::TokenType> operators{
		{"itoa", Token::ITOA},
		{"rho", Token::RHO}
	};

	return operators[op.str()];
}

void Lexer::nextToken(Token &token) {

	// skip white spaces -- any spaces at the begining
	// vector spaces are handled seperately
	while (*BufferPtr && charinfo::isWhiteSpace(*BufferPtr))
		++BufferPtr;

	// if this is the end of input, return that
	if (!*BufferPtr) {
		newToken(token, BufferPtr, Token::EOI);
		return;
	} 

	switch (*BufferPtr) {

	case '+':
		newToken(token, BufferPtr + 1, Token::PLUS);
		return;
	case '-':
		newToken(token, BufferPtr + 1, Token::MINUS);
		return;
	case '/':
		newToken(token, BufferPtr + 1, Token::SLASH);
		return;
	case '*':
		if(*(BufferPtr + 1) == '*') {
			BufferPtr += 1;
			newToken(token, BufferPtr, Token::POWER);
			return;
		}

		if (*BufferPtr == '\0') {
			// guard against an infinite loop
			newToken(token, BufferPtr, Token::ILLEGAL);
			return;
		}
		
		// skip white spaces
		while (*BufferPtr && charinfo::isWhiteSpace(*BufferPtr))
			++BufferPtr;
	case '?':
		newToken(token, BufferPtr + 1, Token::RANDOM);
		return;
	case 'e':
		newToken(token, BufferPtr + 1, Token::E);
		return;
	default:
		if (charinfo::isLetter(*BufferPtr)) {
			// keyword
			const char *end = BufferPtr + 1;
			while(charinfo::isLetter(*end))
				++end;
			llvm::StringRef Literal(BufferPtr, end - BufferPtr);
			newToken(token, end, lookupLongOperator(Literal));
		} else if (charinfo::isDigit(*BufferPtr)) {
			const char *end = BufferPtr + 1;
			while(charinfo::isDigit(*end))
				++end;
			newToken(token, end, Token::NUMBER);
		}
		
		return;
	}
}


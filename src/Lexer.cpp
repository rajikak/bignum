#include "bignum.h"

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
	map<Token::TokenType, string> m{};
}

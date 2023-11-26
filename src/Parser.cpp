#include "bignum.h"
#include "Parser.h"

AST *Parser::parse() {
	AST *Res = parseCalc();
	expect (Token::EOI);
	return Res;
}

AST *Parser::parseCalc() {
	Expression *E;
	E = parseExpr();
	expect(Token::EOI);
	while(Tok.getKind() != Token::EOI)
		advance();
	return nullptr;
}

Expression *Parser::parseExpr(){

	return nullptr;
}

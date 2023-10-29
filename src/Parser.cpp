#include "bignum.h"
#include "Parser.h"

AST *Parser::parse() {
	AST *Res = parseProgram();
	expect (Token::EOI);
	return Res;
}

AST *Parser::parseProgram() {
	Expression *E;
	return nullptr;
}

Expression *Parser::parseStmt(){
	return nullptr;
}

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

Expression *Parser::parseExpr() {
	Expression *Left = parseTerm();
	while (Tok.isOneOf(Token::PLUS, Token::MINUS)) {
		BinaryOp::Operator Op = Tok.is(Token::PLUS)
			? BinaryOp::Plus
			: BinaryOp::Minus;

		advance();
		Expression *Right = parseTerm();
		Left = new BinaryOp(Op, Left, Right);
	}

	return Left;
}

Expression *Parser::parseTerm() {
	Expression *Left = parseFactor();
	while (Tok.isOneOf(Token::ASTERRISK, Token::SLASH)) {
		BinaryOp::Operator Op = Tok.is(Token::ASTERRISK)
			? BinaryOp::Mul
			: BinaryOp::Div;
		advance();
		Expression *Right = parseFactor();
		Left = new BinaryOp(Op, Left, Right);
	}
	return Left;
}

Expression *Parser::parseFactor() {
	Expression *Res = nullptr;
	switch (Tok.getKind()) {
		case Token::NUMBER:
			Res = new Factor(Factor::Number, Tok.getLiteral());
			advance();
			break;
		default:
			if (!Res)
				error();
			while (!Tok.isOneOf(Token::ASTERRISK, 
						Token::PLUS, Token::MINUS, 
						Token::SLASH, Token::EOI))
				advance();
	}
	return Res;
}

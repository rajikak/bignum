#include "bignum.h"
#include "Lexer.h"

using namespace std;

void tokens(vector<string> v) {
	for(string s: v) {
	 	cout << s << ":";
		Lexer Lex(s);
		Token Tok;
		do {
			Lex.nextToken(Tok);
			Lex.printToken(Tok);
		} while (Tok.getType() != Token::EOI);
	}
}


int main() {
	
	vector<string> suite  = {
		"23",
		"     23",
		"23 + 45",
		"23+45",
		"23 +45",
		"23+ 45"
	};

	tokens(suite);
}

#include "bignum.h"
#include "Lexer.h"

using namespace std;

void tokens(vector<string> v) {
	for(string s: v) {
		Lexer Lex(s);
		Token Tok;
		do {
			Lex.nextToken(Tok);
			if (Tok.getType() != Token::EOI && Tok.getType() != Token::COMMENT) {
				Lex.printToken(Tok);
			}
		} while (Tok.getType() != Token::EOI);
	}
}


int main() {
	
	vector<string> suite  = {
		"23",
		"23 + 45",
		"23 - 45",
		"23 / 45",
		"23 * 45",
		"2 ** 2",
		"2 *  * 2",
		"?2",
		"itoa 10",
		"5 rho 1",
		"23 # comment",

	};

	for (string s: suite) {
		cout << s << endl;
	}
	cout << endl;

	tokens(suite);
}

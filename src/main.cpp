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
		"1",
		"2 + 3",
		"4 - 5",
		"6 / 7",
		"8 * 9",
		"10 ** 11",
		"12 ** 13",
		"?14",
		"itoa 15",
		"16 rho 17",
		"18 # comment",
		"10 e 3",
	};

	for (string s: suite) {
		cout << s << endl;
	}
	cout << endl;

	tokens(suite);
}

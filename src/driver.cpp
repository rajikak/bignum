#include "bignum.h"
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include "CodeGen.h"

using namespace std;

/*
 * $ calc "with a: a*3" | llc –filetype=obj –o=expr.o
 * $ clang –o expr expr.o rtcalc.c
 * $ expr
 * Enter a value for a: 4
 * The result is: 12
*/

/**
 * $ ./bigum "2 + 3" | llc -filetype=obj -o=expor.o
 * $ clang -o expr expr.o rtclac.c
 * $ ./expr
 * 5
 */

static llvm::cl::opt<std::string>
	Input(llvm::cl::Positional,
		  llvm::cl::desc("<expression>"),
		  llvm::cl::init(""));

int main(int argc, const char **argv) {
	llvm::InitLLVM X(argc, argv);
	llvm::cl::ParseCommandLineOptions(argc, argv, "bignum - the bignum compiler\n");

	Lexer Lex(Input);
	Parser Parser(Lex);
	AST *Tree = Parser.parse();

	if (!Tree || Parser.hasError()) {
		llvm::errs() << "syntax errors occured\n";
		return 1;
	}

	CodeGen CodeGenerator;
	CodeGenerator.compile(Tree);
	return 0;
}

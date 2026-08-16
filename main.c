#include "stdio.h"
#include "ncc.h"

int main(int argc, char **argv) 
{
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments\n");
		return 1;
	}

	struct lexer *lex = lexer(argv[1]);

	codegen(lex);
	return 0;
}

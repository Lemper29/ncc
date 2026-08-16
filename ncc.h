#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"

enum lexer_kind {
	TOKEN_INT,
	TOKEN_PUNCT,
	TOKEN_END,
};

struct lexer {
	enum lexer_kind kind;
	struct lexer *next_token;
	int val;
	char *loc;
};

struct lexer *lexer(char *p);
void codegen(struct lexer *lex);

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

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

enum parser_kind {
	MUL,
	DIV,
	ADD,
	MINUS,
	NUMBER
};

struct parser {
	enum parser_kind kind;
	struct parser *lhs;
	struct parser *rhs;
	int value;
}; 


struct lexer *lexer(char *p);

struct parser *parser(struct lexer *lex);

void codegen(struct parser *parse);

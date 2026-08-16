#include "ncc.h"

static int get_number(struct lexer *lex) 
{
	if (lex->kind != TOKEN_INT) {
		fprintf(stderr, "Error");
		exit(1);
	};

	return lex->val;
};

void codegen(struct lexer *lex) {
	printf("  .globl main\n");
	printf("main:\n");

	if (lex->kind == TOKEN_INT) {
		printf("  mov $%d, %%rax\n", lex->val);
	}

	while (lex->kind != TOKEN_END) {
		if (lex->kind == TOKEN_PUNCT) {
			if (*lex->loc == '+') {
				printf("  add $%d, %%rax\n", get_number(lex->next_token));
			}
			else if (*lex->loc == '-') {
				printf("  sub $%d, %%rax\n", get_number(lex->next_token));
			}	
		}
		lex = lex->next_token;
	};

	printf("  ret\n");
};

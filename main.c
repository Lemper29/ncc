#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

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

static struct lexer *new_lexer(enum lexer_kind kind, char *loc) 
{
	struct lexer *lex = calloc(1, sizeof(struct lexer));
	lex->kind = kind;
	lex->loc = loc;
	return lex;
};

static int get_number(struct lexer *lex) 
{
	if (lex->kind != TOKEN_INT) {
		fprintf(stderr, "Error");
		exit(1);
	};

	return lex->val;
};

static void lexer_count(struct lexer *lex) 
{
	if (lex->kind == TOKEN_PUNCT) {
		if (*lex->loc == '+') {
			printf("  add $%d, %%rax\n", get_number(lex->next_token));
		}
		else if (*lex->loc == '-') {
			printf("  sub $%d, %%rax\n", get_number(lex->next_token));
		}	
	}
};

static struct lexer *lexer(char *p) 
{
	struct lexer head;
	head.next_token = NULL;
	struct lexer *tok = &head;

	while (*p) {
		if (isspace(*p)) {
			p++;
			continue;
		};

		if (*p == '+' || *p == '-') {
			tok = tok->next_token = new_lexer(TOKEN_PUNCT, p);
			p++;
			continue;
		};

		if (isdigit(*p)) {
			char *endptr;
			tok = tok->next_token = new_lexer(TOKEN_INT, p);
			tok->val = strtoul(p, &endptr, 10);
			p = endptr;
			continue;
		};

		fprintf(stderr, "Error\n");
	}

	tok = tok->next_token = new_lexer(TOKEN_END, p);
	return head.next_token;
};

int main(int argc, char **argv) 
{
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments\n");
		return 1;
	}

	struct lexer *lex = lexer(argv[1]);

	printf("  .globl main\n");
	printf("main:\n");

	if (lex->kind == TOKEN_INT) {
		printf("  mov $%d, %%rax\n", lex->val);
	}

	while (lex->kind != TOKEN_END) {
		lexer_count(lex);
		lex = lex->next_token;
	};

	printf("  ret\n");
	return 0;
}

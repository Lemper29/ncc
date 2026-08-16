#include "ncc.h"

static struct lexer *new_lexer(enum lexer_kind kind, char *loc) 
{
	struct lexer *lex = calloc(1, sizeof(struct lexer));
	lex->kind = kind;
	lex->loc = loc;
	return lex;
};

struct lexer *lexer(char *p) 
{
	struct lexer head;
	head.next_token = NULL;
	struct lexer *tok = &head;

	while (*p) {
		if (isspace(*p)) {
			p++;
			continue;
		};

		if (ispunct(*p)) {
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


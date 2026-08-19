#include "ncc.h"

static struct parser *mul(struct lexer **lex);

static struct parser *new_node(enum parser_kind kind, struct parser *lhs, struct parser *rhs) 
{
	struct parser *node = calloc(1, sizeof(struct parser));
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;

	return node;
};

static bool equal(struct lexer *lex, char *op) 
{
	if (!lex || !lex->loc) return false;

	return lex->loc[0] == op[0];
};

static struct parser *new_num(enum parser_kind kind, int value) 
{
	struct parser *node = calloc(1, sizeof(struct parser));
	node->kind = kind;
	node->value = value;

	return node;
};

static struct parser *get_number(struct lexer **lex) 
{
	struct parser *rhs = mul(lex);

	if (!rhs) {
		exit(1);
	}

	return rhs;
}

static struct parser *primary(struct lexer **lex) 
{
	if ((*lex)->kind == TOKEN_END) {
		return NULL;
	}

	struct parser *node = NULL;

	if ((*lex)->kind == TOKEN_NUMB) {
		node = new_num(ND_NUMB, (*lex)->val);
		*lex = (*lex)->next_token;
		return node;
	}

	return NULL;
};

static struct parser *expr(struct lexer **lex) 
{
	if ((*lex)->kind == TOKEN_END) {
		return NULL;
	}

	struct parser *node = primary(lex);
	if (!node) return NULL;

	if (equal((*lex), "+")) {
		*lex = (*lex)->next_token;
		node = new_node(ND_ADD, node, get_number(lex));
	}
	if (equal((*lex), "-")){
		*lex = (*lex)->next_token;
		node = new_node(ND_MINUS, node, get_number(lex));
	}

	return node;
};

static struct parser *mul(struct lexer **lex) 
{
	if ((*lex)->kind == TOKEN_END) {
		return NULL;
	}

	struct parser *node = primary(lex);

	if (!node) return NULL;
	
	if (equal((*lex), "*")) {
		*lex = (*lex)->next_token;
		node = new_node(ND_MUL, node, get_number(lex));
	}
	if (equal((*lex), "/")) {
		*lex = (*lex)->next_token;
		node = new_node(ND_DIV, node, get_number(lex));
	}

	return node;
};

struct parser *parser(struct lexer *lex) 
{
	struct parser *node = expr(&lex);

	if (lex->kind == TOKEN_END) {
		return node;
	}

	return NULL;
};

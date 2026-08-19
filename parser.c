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

static struct parser *primary(struct lexer **lex) 
{
	if ((*lex)->kind == TOKEN_END) {
		return NULL;
	}

	struct parser *node = NULL;

	if ((*lex)->kind == TOKEN_INT) {
		node = new_num(NUMBER, (*lex)->val);
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
		node = new_node(ADD, node, mul(lex));
	}
	if (equal((*lex), "-")){
		*lex = (*lex)->next_token;
		node = new_node(MINUS, node, mul(lex));
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
		node = new_node(MUL, node, primary(lex));
	}
	if (equal((*lex), "/")) {
		*lex = (*lex)->next_token;
		node = new_node(DIV, node, primary(lex));
	}

	return node;
};

struct parser *parser(struct lexer *lex) 
{
	struct parser *res = expr(&lex);
	return res;
};

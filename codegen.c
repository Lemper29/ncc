#include "ncc.h"

static int get_number(struct parser *node) 
{
	if (node->kind != NUMBER) {
		fprintf(stderr, "Error");
		exit(1);
	};

	return node->value;
};

static void print_asm(struct parser *node) {
	if (!node) {return;};
	
	if (node->kind == NUMBER) {
		printf("  mov $%d, %%rax\n", get_number(node));
		return;
	}

	print_asm(node->lhs);

	printf("  push %%rax\n");

	print_asm(node->rhs);

	printf("  pop %%rbx\n");

	switch (node->kind) {
		case ADD:
			printf("  add %%rbx, %%rax\n");
			break;
		case MINUS:
			printf("  sub %%rax, %%rbx\n");
			printf("  mov %%rbx, %%rax\n");
			break;
		case MUL:
			printf("  imul %%rbx, %%rax\n");
			break;
		case DIV:
			printf("  xor %%rdx, %%rdx\n");
			printf("  div %%rbx\n");
			break;
		default:
			break;
	}
};

void codegen(struct parser *node) {
	if (!node) {return;};

	printf("  .globl main\n");
	printf("main:\n");
	
	print_asm(node);

	printf("  ret\n");
};

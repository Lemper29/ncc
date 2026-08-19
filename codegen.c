#include "ncc.h"

static void print_asm(struct parser *node) 
{
	if (!node) {return;};

	if (node->kind == ND_NUMB) {
		printf("  mov $%d, %%rax\n", node->value);
		return;
	}

	print_asm(node->lhs);

	printf("  push %%rax\n");

	print_asm(node->rhs);

	printf("  pop %%rbx\n");

	switch (node->kind) {
		case ND_ADD:
			printf("  add %%rbx, %%rax\n");
			break;
		case ND_MINUS:
			printf("  sub %%rax, %%rbx\n");
			printf("  mov %%rbx, %%rax\n");
			break;
		case ND_MUL:
			printf("  imul %%rbx, %%rax\n");
			break;
		case ND_DIV:
			printf("  xor %%rdx, %%rdx\n");
			printf("  div %%rbx\n");
			break;
		default:
			break;
	}
};

void codegen(struct parser *node) 
{
	if (!node) {return;};

	printf("  .globl main\n");
	printf("main:\n");
	
	print_asm(node);

	printf("  ret\n");
};

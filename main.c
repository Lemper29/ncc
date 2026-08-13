#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments\n");
		return 1;
	}

	char *p = argv[1];

	printf("  .globl main\n");
	printf("main:\n");
	printf("  mov $%ld, %%rax\n", strtol(p, &p, 10));

	while (*p) {
		if (*p == '+') {
			p++;
			printf("  add $%ld, %%rax\n", strtol(p, &p, 10));
			continue;
		}
		if (*p == '-') {
			p++;
			printf("  sub $%ld, %%rax\n", strtol(p, &p, 10));
			continue;
		}

		fprintf(stderr, "unexpected character: '%c'\n", *p);
		return 1;
	}

	printf("  ret\n");
}

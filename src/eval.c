#include "mpc/mpc.h"

#include "mystr.h"

#include "eval.h"

static long eval_op(char *op, long x, long y) {
	if (!strdiff(op, "+")) return x + y;
	if (!strdiff(op, "-")) return x - y;
	if (!strdiff(op, "*")) return x * y;
	if (!strdiff(op, "/")) return x / y;
	return 0;
}

long eval(mpc_ast_t *t) {
	if (strcont(t->tag, "num")) {
		return atoi(t->contents);
	}

	char *op = t->children[1]->contents;

	long x = eval(t->children[2]);
	int i = 3;
	while (strcont(t->children[i]->tag, "exp")) {
		x = eval_op(op, x, eval(t->children[i]));
		i++;
	}

	return x;
}

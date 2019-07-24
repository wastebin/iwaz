#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <histedit.h>

#include "mpc/mpc.h"
#include "mystr.h"

#include "defs.a.h"

#include "eval.h"

int main(int argc, char **argv) {
	mpc_parser_t *Num = mpc_new("num");
	mpc_parser_t *Op  = mpc_new("op");
	mpc_parser_t *Exp = mpc_new("exp");
	mpc_parser_t *Top = mpc_new("top");

	mpca_lang(MPCA_LANG_DEFAULT,
		"num : /-?[0-9]+/ ; "
		"op  : /[+\\-*\\/]/ ; "
		"exp : <num> | '(' <op> <exp>+ ')' ; "
		"top : /^/ <op> <exp>+ /$/ ; ",
		Num, Op, Exp, Top
	);

	puts("Īwaz " VERSION);
	puts("Press ^C to exit. Please don’t press ^D. It makes editline segfault.");

	while (1) {
		char *inp = readline("% ");

		add_history(inp);

		mpc_result_t r;
		if (mpc_parse("<stdin>", inp, Top, &r)) {
			long res = eval(r.output);
			printf("%li\n", res);

			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		free(inp);
	}

	mpc_cleanup(4, Num, Op, Exp, Top);

	return 0;
}

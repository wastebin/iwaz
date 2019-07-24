#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <histedit.h>

int main(int argc, char **argv) {
	puts("Īwaz v0.1.0");
	puts("Press ^C to exit. Please don’t press ^D. It makes editline segfault.");

	while (1) {
		char *inp = readline("% ");

		add_history(inp);

		free(inp);
	}

	return 0;
}

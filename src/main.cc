#include <stdio.h>

#include <vector>

#include "str.hh"

#include "reader.hh"

int main(int argc, char **argv) {
	fputs("Īwaz 0.1.0\n", stdout);
	fputs("Press ^C to exit\n\n", stdout);

	reader r;

	while (true) {
		const char *line = r.read_line("% ")->c_str();
		if (!strdiff(line, "\x03")) break;
		puts(line);
	}
}

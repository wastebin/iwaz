#include <ctype.h>
#include <stdio.h>
#include <termios.h>

#include <memory>
#include <string>
#include <vector>

#include "str.hh"

#include "reader.hh"

reader::reader() {
	tcgetattr(0, &orig);

	auto raw = orig;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSAFLUSH, &raw);
}
reader::~reader() {
	tcsetattr(0, TCSAFLUSH, &orig);
}

std::string *reader::read_line(const char *ps1) {
	fputs(ps1, stdout);
	auto str = new std::string;
	while (true) {
		char c = getchar();
		switch (c) {
			case '\b':
				str->pop_back();
				fputs("\b \b", stdout);
				break;
			case '\n':
				hist.emplace_back(str);
				puts("");
				return str;
			case '\x03':
				if (str->length()) {
					puts("");
					return read_line(ps1);
				}
				else {
					str->push_back(Ctrl<'C'>);
					hist.emplace_back(str);
					puts("^C");
					return str;
				}
			default:
				str->push_back(c);
				fputc(c, stdout);
		}
	}
}

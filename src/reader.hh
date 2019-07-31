#pragma once

#ifndef _READER_HH
#define _READER_HH

#include <termios.h>

#include <memory>
#include <string>
#include <vector>

class reader {
	public:
		reader();
		~reader();

		std::string *read_line(const char *);

	private:
		termios orig;
		std::vector<std::unique_ptr<std::string>> hist;
};

#endif

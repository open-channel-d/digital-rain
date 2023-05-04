#pragma once
#include <iostream>

enum FormatAttr {
	FMT_DEFAULT = 0,
	BOLD,
	DIM,
	ITALICS,
	UNDERLINED,
	BLINK,
	REVERSE,
	HIDDEN
};

enum Color {
	DEFAULT = 39,
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	LIGHTGRAY,
	DARKGRAY = 90,
	LIGHTRED,
	LIGHTGREEN,
	LIGHTYELLOW,
	LIGHTBLUE,
	LIGHTMAGENTA,
	LIGHTCYAN,
	WHITE
};

template <typename T>
void printColored(const T &text, Color color = DEFAULT, FormatAttr fmt = FMT_DEFAULT) {
	std::cout << "\033[" << fmt << ";" << color << "m" << text << "\033[0m";
}
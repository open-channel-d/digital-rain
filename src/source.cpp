#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <cstring>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "ColoredPrint.h"

std::string letters = "ABCDEFGHIJKLMNOPQRSTWUVXYZ";

Color colorFromString(const std::string &str) {
	if (str == "black") {
		return BLACK;
	}
	if (str == "red") {
		return RED;
	}
	if (str == "green") {
		return GREEN;
	}
	if (str == "yellow") {
		return YELLOW;
	}
	if (str == "blue") {
		return BLUE;
	}
	if (str == "magenta") {
		return MAGENTA;
	}
	if (str == "cyan") {
		return CYAN;
	}
	if (str == "lightred") {
		return LIGHTRED;
	}
	if (str == "lightgreen") {
		return LIGHTGREEN;
	}
	if (str == "lightyellow") {
		return LIGHTYELLOW;
	}
	if (str == "lightblue") {
		return LIGHTBLUE;
	}
	if (str == "lightcyan") {
		return LIGHTCYAN;
	}
	if (str == "lightmagenta") {
		return LIGHTMAGENTA;
	}
	if (str == "white") {
		return WHITE;
	}
	return DEFAULT;
}

class RainDrop {
public:
	RainDrop(int field_height, int len, Color color) : len(len), chars(field_height), y_start(-len), color(color) {
		for (size_t i = 0; i < field_height; ++i) {
			chars[i] = letters[rand() % letters.size()];
		}
	};
	void move() {
		++y_start;
	}

	FormatAttr getFormat(int y) {
		if (y == y_start + len - 1) {
			return BOLD;
		}
		if (y < y_start + 3) {
			return DIM;
		}
		return FMT_DEFAULT;
	}

	size_t len;
	std::vector<char> chars;
	int y_start;
	Color color;
};

class Field {
public:
	Field(size_t weight, size_t height, const std::vector<Color> &colors)
		: weight(weight), height(height), drops(weight), colors(colors)
	{
	}
	void draw() {
		for (int y = 0; y < height; ++y) {
			for (size_t x = 0; x < weight; ++x) {
				if (!drops[x]) {
					std::cout << " ";
					continue;
				}
				if (y >= drops[x]->y_start && y < drops[x]->y_start + drops[x]->len) {
					printColored(drops[x]->chars[y], drops[x]->color, drops[x]->getFormat(y));
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << "\n";
		}
	}

	void addRandom() {
		constexpr size_t MIN_LEN = 3;
		size_t random = rand() % weight;
		if (drops[random]) {
			return;
		}
		size_t random_len = MIN_LEN + rand() % (height - MIN_LEN);
		size_t random_color = rand() % colors.size();
		drops[random] = std::make_shared<RainDrop>(height, random_len, colors[random_color]);
	}

	void move() {
		for (auto& drop : drops) {
			if (drop) {
				drop->move();
				if (drop->y_start >= height) {
					drop.reset();
				}
			}
		}
	}
private:
	int weight;
	int height;
	std::vector<std::shared_ptr<RainDrop>> drops;
	Color color;
	std::vector<Color> colors;
};

int main(int argc, char *argv[]) {
	srand(time(NULL));
	std::vector<Color> colors;

	if (argc > 1) {
		for (size_t i = 1; i < argc; ++i) {
			colors.push_back(colorFromString(argv[i]));
		}
	}
	else {
		colors.push_back(GREEN);
	}
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	Field field(w.ws_col, w.ws_row, colors);
	field.addRandom();
	while (true) {
		system("clear");
		field.draw();
		field.move();
		if (rand() % 3) {
			field.addRandom();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}
	return 0;
}

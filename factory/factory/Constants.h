#pragma once
#include <map>

enum class Color 
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

static const std::map<Color, std::string> COLOR_TO_STR_LIST = {
	{ Color::Green, "Green" },
	{ Color::Red, "Red" },
	{ Color::Blue, "Blue" },
	{ Color::Yellow, "Yellow" },
	{ Color::Pink, "Pink" },
	{ Color::Black, "Black" }
};

static const std::map<std::string, Color> STR_TO_COLOR_LIST = {
	{ "Green", Color::Green },
	{ "Red", Color::Red },
	{ "Blue", Color::Blue },
	{ "Yellow", Color::Yellow },
	{ "Pink", Color::Pink },
	{ "Black", Color::Black }
};

struct Vector2 
{
	Vector2() = default;
	Vector2(double x, double y)
		: x(x)
		, y(y)
	{}

	double x;
	double y;
};
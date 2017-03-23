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

static const std::map<Color, std::string> COLOR_STR_MAP = {
	{ Color::Green, "Green" },
	{ Color::Red, "Red" },
	{ Color::Blue, "Blue" },
	{ Color::Yellow, "Yellow" },
	{ Color::Pink, "Pink" },
	{ Color::Black, "Black" }
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
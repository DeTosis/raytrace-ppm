#pragma once
#include <cstdint>
#include <fstream>

typedef uint32_t ui32;
typedef int32_t i32;
typedef uint8_t ui8;

class Color {
public:
	ui8 r,g,b;
public:
	Color(){ r = 0; g = 0; b = 0; };
	Color(ui8 r, ui8 g, ui8 b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	};
};

struct i32vec2 {
public:
	i32 x, y;
};


struct ui32vec2 {
public:
	ui32 x, y;

};

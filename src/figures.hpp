#pragma once
#include <unordered_set>
#include "types.hpp"

class Image;
class Pixel;

class Figure {
private:
	std::unordered_set<ui32vec2> m_used_pixels;
protected:
	Image* r_img;
	ui32vec2 r_box_size;
	ui32vec2 r_origin;
	Color r_color;
	
	void add_pixel(ui32 x, ui32 y);
public:
	Figure(
		Image *img, ui32vec2 box_size, 
		ui32vec2 origin, Color color);

	bool is_pixel_set(ui32 x, ui32 y);
};

class Rect : public Figure {
public:
	Rect(
		Image* img, 
		ui32vec2 box_size, ui32vec2 origin, Color fill_color);
private:
	void draw();
};

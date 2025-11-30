#pragma once
#include "image.hpp"
#include "types.hpp"

class Figure {
private:
	ui32 m_size = 0;
	Pixel** m_used_pixels;
protected:
	Image* r_img;
	ui32vec2 r_box_size;
	ui32vec2 r_origin;
	Color r_color;
	
	void add_pixel(int32_t x, int32_t y);
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

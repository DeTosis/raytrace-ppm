#pragma once
#include <iostream>
#include <vector>
#include "types.hpp"

class Figure;

class Pixel {
private:
	ui32 m_x = -1,m_y = -1;
	Color m_color;
public:
	Pixel(ui32 x, ui32 y, Color color = {0,0,0}) 
	{
		m_x = x;
		m_y = y;
		m_color = color;
	};

	ui32vec2 get_position() { return { m_x, m_y }; };
	Color getColor() { return m_color; };
	void set_color(Color color) { m_color = color; };
};

class Image {
private:
	const char* m_magic = "P6\n"; 
	std::string m_header;
	const char* m_fname;
	ui32 m_height;
	ui32 m_width;
	Pixel* pixels;
	std::vector<Figure*> m_figures;
public:
	Image(const char* f_name, ui32 width, ui32 height);
	void init();
	void save(const char* path = "./");
	void set_pixel_color(ui32 x, ui32 y, Color color);
	Pixel* get_pixel(ui32 x, ui32 y) 
		{ return &pixels[y * m_width + x]; };
	ui32vec2 get_box_size() { return { m_width, m_height }; };;
	void add_figure_to_cene(Figure* figure) { m_figures.push_back(figure); };
	std::vector<Figure*>* get_figures() { return &m_figures; };
};

#include "figures.hpp"

void Figure::add_pixel(int32_t x, int32_t y) {
	m_used_pixels[m_size] = r_img->get_pixel(x,y);
	m_size++;
};

Figure::Figure(
		Image *img, ui32vec2 box_size, 
		ui32vec2 origin, Color color) {
	r_img = img;
	r_box_size = box_size;
	r_origin = origin;
	r_color = color;
	m_used_pixels = (Pixel**)malloc(
			sizeof(Pixel*) * r_box_size.x * r_box_size.y); 
};

bool Figure::is_pixel_set(ui32 x, ui32 y) {
	for (ui32 i = 0; i < m_size; i++) {
		Pixel* p = m_used_pixels[i];
		ui32vec2 pos = p->get_position();
		if (pos.x == x && pos.y == y) {
			return true;
		};
	};
	return false;
};

Rect::Rect(
		Image* img, 
		ui32vec2 box_size, ui32vec2 origin, Color fill_color) 
	: Figure(img, box_size, origin, fill_color) { draw(); };

void Rect::draw() {
	for (int x = r_origin.x; x < (int)(r_origin.x + r_box_size.x); x++) {
		for (int y = r_origin.y; y < (int)(r_origin.y + r_box_size.y); y++) {
			r_img->set_pixel_color((ui32)x,(ui32)y,r_color);
			add_pixel(x,y);
		};
	};
	r_img->add_figure_to_cene(this);
};

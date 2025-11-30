#include "figures.hpp"
#include "image.hpp"

void Figure::add_pixel(ui32 x, ui32 y) {
	m_used_pixels.insert({x,y});
};

Figure::Figure(
		Image *img, ui32vec2 box_size, 
		ui32vec2 origin, Color color) {
	r_img = img;
	r_box_size = box_size;
	r_origin = origin;
	r_color = color;
};

bool Figure::is_pixel_set(ui32 x, ui32 y) {
	auto it = m_used_pixels.find({x,y});
	if (it != m_used_pixels.end()) { return true; }
	return false;
};

Rect::Rect(
		Image* img, 
		ui32vec2 box_size, ui32vec2 origin, Color fill_color) 
	: Figure(img, box_size, origin, fill_color) { draw(); };

void Rect::draw() {
	for (ui32 x = r_origin.x; x < (r_origin.x + r_box_size.x); x++) {
		for (ui32 y = r_origin.y; y < (r_origin.y + r_box_size.y); y++) {
			r_img->set_pixel_color(x,y,r_color);
			if (x == r_origin.x) { add_pixel(x,y); }
			if (x == (r_origin.x + r_box_size.x) - 1) { add_pixel(x,y); }
			if (y == r_origin.y) { add_pixel(x,y); }
			if (y == (r_origin.y + r_box_size.y) - 1) { add_pixel(x,y); }
		};
	};
	r_img->add_figure_to_cene(this);
};

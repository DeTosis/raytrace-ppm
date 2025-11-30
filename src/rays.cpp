#include "rays.hpp"

Ray::Ray(Image* img, ui32vec2 origin, int max_steps, Color trace_color, float step_size) {
	m_img = img;
	m_origin = origin;
	m_max_steps = max_steps;
	m_trace_color = trace_color;
	m_step_size = step_size;
};

void Ray::cast(float angle) {
	ui32vec2 dim = m_img->get_box_size();		
	angle = 360.0f - angle;

	float dx = std::cos(angle * M_PI / 180);
	float dy = std::sin(angle * M_PI / 180);

	float rx = m_origin.x;
	float ry = m_origin.y;
	for (int i = 0; i < m_max_steps; i++) {
		rx += dx * m_step_size;
		ry += dy * m_step_size;
		if ( ry > 0 && ry < dim.y - 1 && rx > 0 && rx < dim.x - 1) {
			auto figures = m_img->get_figures();
			for (const auto& f : *figures) {
				if (f->is_pixel_set(std::ceil(rx),std::ceil(ry))) {
					return;
				};
			};
			m_img->set_pixel_color(rx,ry, m_trace_color);
		}
		else
			break;
	};
};


#include <iostream>
#include <any>
#include <cmath>
#include <memory>

#include "src/image.hpp"
#include "src/figures.hpp"

std::ostream& operator<<(std::ostream& os, ui32vec2 v)
{
	os << "{" << v.x << ", " << v.y << "}"; 
	return os;
};

class Ray
{
private:
	Image* m_img;
	ui32vec2 m_origin;
	int m_max_steps;
	Color m_trace_color;
	float m_step_size;
public:
	Ray(Image* img, ui32vec2 origin, int max_steps, Color trace_color, float step_size = 1)
	{
		m_img = img;
		m_origin = origin;
		m_max_steps = max_steps;
		m_trace_color = trace_color;
		m_step_size = step_size;
	};

	void cast(float angle) 
	{
		ui32vec2 dim = m_img->get_box_size();		
		angle = 360.0f - angle;

		float dx = std::cos(angle * M_PI / 180);
		float dy = std::sin(angle * M_PI / 180);

		float rx = m_origin.x;
		float ry = m_origin.y;
		for (int i = 0; i < m_max_steps; i++)
		{
			rx += dx * m_step_size;
			ry += dy * m_step_size;
			if ( ry > 0 && ry < dim.y - 1 && rx > 0 && rx < dim.x - 1)
			{
				auto figures = m_img->get_figures();
				for (const auto& f : *figures)
				{
					if (f->is_pixel_set(std::ceil(rx),std::ceil(ry)))
					{
						return;
					};
				};
				m_img->set_pixel_color(rx,ry, m_trace_color);
			}
			else
				break;
		};
	};
};

int main(){
	Image image("test", 1000, 1000);
	image.init();

	Rect r0(&image, {150,150}, {675, 175}, {100,100,100});

	Ray ray(&image, {500,500}, 10000, {255,255,255});
	for (float i = 0; i < 360; i+= 0.1)
	{
		ray.cast(i);
	};
	image.save();
};

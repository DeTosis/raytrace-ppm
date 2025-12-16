#pragma once
#include <cmath>

#include "image.hpp"
#include "types.hpp"

class Ray
{
private:
	Image* m_img;
	ui32vec2 m_origin;
	int m_max_steps;
	Color m_trace_color;
	float m_step_size;
public:
	Ray(Image* img, ui32vec2 origin, int max_steps, Color trace_color);
	void cast(float angle);
};

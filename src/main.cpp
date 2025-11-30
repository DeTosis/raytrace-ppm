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

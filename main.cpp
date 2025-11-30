#include <iostream>
#include <any>
//#include <memory>

#include "src/image.hpp"
#include "src/figures.hpp"
#include "src/rays.hpp"

std::ostream& operator<<(std::ostream& os, ui32vec2 v)
{
	os << "{" << v.x << ", " << v.y << "}"; 
	return os;
};

#include <chrono>

int main(){
	Image image("test", 1000, 1000);
	image.init();

	Rect r0(&image, {150,150}, {675, 175}, {100,100,100});
	Rect r1(&image, {250,250}, {175, 475}, {100,100,100});

	Ray ray(&image, {500,500}, 10000, {255,255,255});

	auto start_t = std::chrono::high_resolution_clock::now();
	ui32 rayc = 0;
	for (float i = 0; i < 360; i+= 0.01)
	{
		ray.cast(i);
		rayc++;
	};
	auto end_t = std::chrono::high_resolution_clock::now();
	auto duration = end_t - start_t;
	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	long long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	std::cout << "Execution time: " << seconds << "s" << std::endl;
	std::cout << "Rays casted: " << rayc << std::endl;
	std::cout << "Average time per ray cast: " << (float)seconds / (float)rayc << std::endl;

	Rect origin(&image, {5,5}, {500, 500}, {255,0,0});
	image.save();
};

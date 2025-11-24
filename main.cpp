#include <iostream>
#include <cstdint>
#include <fstream>
#include <any>
#include <cmath>
#include <vector>
#include <memory>


class Figure;

class Color
{
public:
	uint8_t r,g,b;
public:
	Color(){ r = 0; g = 0; b = 0; };
	Color(uint8_t r, uint8_t g, uint8_t b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	};
};

struct i32vec2
{
public:
	int32_t x, y;
};


struct ui32vec2
{
public:
	uint32_t x, y;

};

std::ostream& operator<<(std::ostream& os, ui32vec2 v)
{
	os << "{" << v.x << ", " << v.y << "}"; 
	return os;
};

class Pixel
{
private:
	uint32_t m_x = -1,m_y = -1;
	Color m_color;
public:
	Pixel(uint32_t x, uint32_t y, Color color = {0,0,0}) 
	{
		m_x = x;
		m_y = y;
		m_color = color;
	};

	ui32vec2 get_position() { return { m_x, m_y }; };
	Color getColor() { return m_color; };

	void set_color(Color color) { m_color = color; };
};

class Image
{
private:
	const char* m_magic = "P6\n"; 
	std::string m_header;
	const char* m_fname;
	uint32_t m_height;
	uint32_t m_width;
	Pixel* pixels;
	std::vector<Figure*> m_figures;
public:
	Image(const char* f_name, uint32_t width, 
		uint32_t height)
	{
		m_fname = f_name;
		m_height = height;
		m_width = width;
	};
	void init()
	{
		m_header += m_magic;
		m_header += 
			std::to_string(m_width) + " " + std::to_string(m_height) + "\n";
		m_header += "255\n";

		pixels = (Pixel*)malloc(sizeof(Pixel) * m_width * m_height);
		uint32_t index = 0;
		for ( uint32_t y = 0; y < m_height; y++ )	
		{
			for ( uint32_t x = 0; x < m_width; x++ )
			{
				pixels[index] = Pixel(x,y, {128,128,128});	
				index++;
			};
		};
	};
	void save(const char* path = "./")
	{
		std::string f_path = std::string(path) + m_fname + ".ppm"; 
		std::ofstream ofs(f_path, std::ios::binary);
		if (!ofs) 
		{
			std::cout << "[ ERR ] Could not save file at path: "
				<< f_path << std::endl; 
			return;
		};
		
		ofs << m_header;
		for ( uint32_t index = 0; index < m_width * m_height; index++ )
		{
			Pixel pixel = pixels[index];
			Color c = pixel.getColor();
			ofs.put(c.r);
			ofs.put(c.g);
			ofs.put(c.b);
		};
		ofs.close();
	};
	
	void set_pixel_color(uint32_t x, uint32_t y, Color color)
	{
		uint32_t index = y * m_width + x;
		pixels[index].set_color(color);
	};
	
	Pixel* get_pixel(uint32_t x, uint32_t y)
	{
		return &pixels[y * m_width + x];
	};
	
	ui32vec2 get_box_size() { return { m_width, m_height }; };

	void add_figure_to_cene(Figure* figure)
	{
		m_figures.push_back(figure);
	};

	std::vector<Figure*>* get_figures()
	{
		return &m_figures;
	};
};

// *** FIGURES ***

class Figure
{
private:
	uint32_t m_size = 0;
	Pixel** m_used_pixels;
protected:
	Image* r_img;
	ui32vec2 r_box_size;
	ui32vec2 r_origin;
	Color r_color;
protected:
	void add_pixel(int32_t x, int32_t y)
	{
		m_used_pixels[m_size] = r_img->get_pixel(x,y);
		m_size++;
	};
public:
	Figure(
		Image *img, 
		ui32vec2 box_size, 
		ui32vec2 origin, 
		Color color)
	{
		r_img = img;
		r_box_size = box_size;
		r_origin = origin;
		r_color = color;
		m_used_pixels = (Pixel**)malloc(
			sizeof(Pixel*) * r_box_size.x * r_box_size.y);
	};
	bool is_pixel_set(uint32_t x, uint32_t y)
	{
		for (uint32_t i = 0; i < m_size; i++)
		{
			Pixel* p = m_used_pixels[i];
			ui32vec2 pos = p->get_position();
			if (pos.x == x && pos.y == y)
			{
				return true;
			};
		};
		return false;
	};
};

class Rect : public Figure
{
public:
	Rect(
		Image* img, 
		ui32vec2 box_size, ui32vec2 origin, Color fill_color) 
			: Figure(img, box_size, origin, fill_color)
	{
		draw();
	};

private:
	void draw()
	{
		for (int x = r_origin.x; x < (int)(r_origin.x + r_box_size.x); x++) 
		{
			for (int y = r_origin.y; y < (int)(r_origin.y + r_box_size.y); y++) 
			{
				r_img->set_pixel_color((uint32_t)x,(uint32_t)y,r_color);
				add_pixel(x,y);
			};
		};
		r_img->add_figure_to_cene(this);
	};
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

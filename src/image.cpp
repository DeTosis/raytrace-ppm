#include "image.hpp"
#include "figures.hpp"

Image::Image(const char* f_name, uint32_t width, 
		uint32_t height) {
	m_fname = f_name;
	m_height = height;
	m_width = width;
};

void Image::init() {
	m_header += m_magic;
	m_header += 
		std::to_string(m_width) + " " + std::to_string(m_height) + "\n";
	m_header += "255\n";

	pixels = (Pixel*)malloc(sizeof(Pixel) * m_width * m_height);
	uint32_t index = 0;
	for ( uint32_t y = 0; y < m_height; y++ ) {
		for ( uint32_t x = 0; x < m_width; x++ ) {
			pixels[index] = Pixel(x,y, {128,128,128});	
			index++;
		};
	};
};

void Image::save(const char* path) stdio{
	std::string f_path = std::string(path) + m_fname + ".ppm"; 
	std::ofstream ofs(f_path, std::ios::binary);
	if (!ofs) {
		std::cout << "[ ERR ] Could not save file at path: "
			<< f_path << std::endl; 
		return;
	};

	ofs << m_header;
	for ( uint32_t index = 0; index < m_width * m_height; index++ ) {
		Pixel pixel = pixels[index];
		Color c = pixel.getColor();
		ofs.put(c.r);
		ofs.put(c.g);
		ofs.put(c.b);
	};
	ofs.close();
};

void Image::set_pixel_color(uint32_t x, uint32_t y, Color color) {
	uint32_t index = y * m_width + x;
	pixels[index].set_color(color);
};

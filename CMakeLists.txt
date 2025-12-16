cmake_minimum_required(VERSION 3.20)

project(raytrace-ppm LANGUAGES CXX)

add_executable(raytrace-ppm
	src/figures.cpp
	src/image.cpp
	src/rays.cpp
	src/main.cpp
)

#include "RenderData.h"
#include <cstring>

#include "print.h"

Color::Color(int r, int g, int b, int a) {
	if (r < 0)
		this->r = 0;
	else if (r > 255)
		this->r = 255;
	else
		this->r = (byte) r;

	if (g < 0)
		this->g = 0;
	else if (g > 255)
		this->g = 255;
	else
		this->g = g;

	if (b < 0)
		this->b = 0;
	else if (b > 255)
		this->b = 255;
	else
		this->b = (byte) b;

	if (a < 0)
		this->a = 0;
	else if (a > 255)
		this->a = 255;
	else
		this->a = (byte) a;
}

RenderData::RenderData(int width, int height) : width(width), height(height) {
	data = new unsigned int[width * height];
}

RenderData::RenderData(int width, int height, void* data) : width(width), height(height), data((unsigned int*) data) {}

RenderData::RenderData(const RenderData& src) {
	width = src.width;
	height = src.height;

	data = new unsigned int[width * height];
	std::memcpy(data, src.data, width * height * sizeof(int));
}

int RenderData::getWidth() {
	return width;
}

int RenderData::getHeight() {
	return height;
}

void RenderData::setPixel(int x, int y, Color color) {
	unsigned int c = (((int) color.a) << 24) | (((int) color.b) << 16) | (((int) color.g) << 8) | ((int) color.r);

	data[width * y + x] = c;
}

Color RenderData::getPixel(int x, int y) {
	unsigned int color = data[width * y + x];

	byte a = (color >> 24) & 0xFF;
	byte b = (color >> 16) & 0xFF;
	byte g = (color >> 8) & 0xFF;
	byte r = (color) & 0xFF;

	return Color(r, g, b, a);
}

void RenderData::destroy() {
	delete[] data;
}

void* RenderData::getData() {
	return data;
}
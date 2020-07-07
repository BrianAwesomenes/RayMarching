#pragma once

#include <cstdint>

typedef std::uint8_t byte;

struct Color {
	byte r;
	byte g;
	byte b;
	byte a;

	//Color(byte r, byte g, byte b, byte a = 255) : r(r), g(g), b(b), a(a) {}
	Color(int r, int g, int b, int a = 255);
};

class RenderData
{
	int width;
	int height;
	unsigned int* data;

	~RenderData() {}
public:
	RenderData(int width, int height);
	RenderData(int width, int height, void* data);
	RenderData(const RenderData& src);

	int getWidth();
	int getHeight();

	void setPixel(int x, int y, Color color);
	Color getPixel(int x, int y);

	void* getData();

	void destroy();
};


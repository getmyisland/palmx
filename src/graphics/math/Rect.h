#ifndef RECT_H
#define RECT_H
#ifdef _WIN32
#pragma once
#endif

#include "../Prequisites.h"

class Rect
{
public:
	Rect() {}
	Rect(i32 width, i32 height):width(width),height(height) {}
	Rect(i32 width, i32 height, i32 left, i32 top):width(width), height(height), left(left), top(top) {}
	Rect(const Rect& rect) :width(rect.width), height(rect.height), left(rect.left), top(rect.top) {}

	i32 width = 0;
	i32 height = 0;
	i32 left = 0;
	i32 top = 0;
};

#endif // RECT_H
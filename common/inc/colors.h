#ifndef COLORS_H
#define COLORS_H

#include "algebra/vector4.hpp"

namespace colors
{
	enum color_type{BLUE=0, GREEN, RED, BLACK, WHITE};
	static algebra::vector4<float> GetColor(color_type c)
	{
		algebra::vector4<float> clr;
		switch (c)
		{
		case BLUE: clr = algebra::vector4<float>(0.0f, 0.0f, 1.0f, 1.0f); break;
		case GREEN: clr = algebra::vector4<float>(0.0f, 1.0f, 0.0f, 1.0f); break;
		case RED: clr = algebra::vector4<float>(1.0f, 0.0f, 0.0f, 1.0f); break;
		case BLACK: clr = algebra::vector4<float>(0.0f, 0.0f, 0.0f, 1.0f); break;
		case WHITE: clr = algebra::vector4<float>(1.0f, 1.0f, 1.0f, 1.0f); break;
		}
		return clr;
	}
}

#endif
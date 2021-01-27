#include "PaintTool.h"

#include <iostream>
#include <cmath>

PaintTool::PaintTool(Canvas* canvas) noexcept
	:Tool{ canvas }, state{0}
{}

void PaintTool::onMouseClick(int x, int y)
{
	state = BIT(0);

	paint_radius(x, y);

	lastPos = sf::Vector2i{ x, y };
}

void PaintTool::onMouseMoved(int x, int y)
{
	if ((state & BIT(0)) > (char)0)
	{
		paint_radius(x, y);

		double dy = static_cast<double>(y - lastPos.y);
		double dx = static_cast<double>(x - lastPos.x);
		if (dx != 0)
		{
				//interpolate all of the values between the current pos and the last pos
				//find the gradient
				double grad = dy / dx;
				double c = y - (grad * x);

				//find all of the y pos
				if (dy > 0)
				{
					for (size_t i = y; i > lastPos.y; i--)
					{
						paint_radius((i - c) / grad, i);
					}					
				}
				else if (dy < 0)
				{
					for (size_t i = y; i < lastPos.y; i++)
					{
						paint_radius((i - c) / grad, i);
					}
				}

				if (dx > 0)
				{
					for (size_t i = x; i > lastPos.x; i--)
					{
						paint_radius(i, (grad * i) + c);
					}
				}
				else if (dx < 0)
				{
					for (size_t i = x; i < lastPos.x; i++)
					{
						paint_radius(i, (grad * i ) + c);
					}
				}
		}
		else
		{
			//in case there was a change in why but not x
			if (dy > 0)
			{
				for (size_t i = y; i > lastPos.y; i--)
				{
					paint_radius(x, i);
				}
			}
			else if (dy < 0)
			{
				for (size_t i = y; i < lastPos.y; i++)
				{
					paint_radius(x, i);
				}
			}
		}

		lastPos = sf::Vector2i{ x, y };
	}
	
	
}

void PaintTool::onMouseRelease()
{
	state ^= BIT(0);
}

void PaintTool::paint_radius(int x, int y)
{
	// square drawing
	for (size_t i = 0; i < size; i++)
	{
		for (size_t z = 0; z < size; z++)
		{
			canvas->changePixel(x + z, y + i);
			canvas->changePixel(x + z, y - i);

			canvas->changePixel(x - z, y + i);
			canvas->changePixel(x - z, y - i);
		}
	}

}

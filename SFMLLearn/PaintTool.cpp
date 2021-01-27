#include "PaintTool.h"

#include <iostream>

PaintTool::PaintTool(Canvas* canvas) noexcept
	:Tool{ canvas }, state{0}
{}

void PaintTool::onMouseClick(int x, int y)
{
	state = BIT(0);

	canvas->changePixel(x, y);

	lastPos = sf::Vector2i{ x, y };
}

void PaintTool::onMouseMoved(int x, int y)
{
	if ((state & BIT(0)) > (char)0)
	{
		canvas->changePixel(x, y);

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
						canvas->changePixel((i - c) / grad, i);
					}					
				}
				else if (dy < 0)
				{
					for (size_t i = y; i < lastPos.y; i++)
					{
						canvas->changePixel((i - c) / grad, i);
					}
				}

				if (dx > 0)
				{
					for (size_t i = x; i > lastPos.x; i--)
					{
						canvas->changePixel(i, (grad * i) + c);
					}
				}
				else if (dx < 0)
				{
					for (size_t i = x; i < lastPos.x; i++)
					{
						canvas->changePixel(i, (grad * i ) + c);
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
					canvas->changePixel(x, i);
				}
			}
			else if (dy < 0)
			{
				for (size_t i = y; i < lastPos.y; i++)
				{
					canvas->changePixel(x, i);
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
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
		

		double dy = static_cast<double>(y - lastPos.y);
		double dx = static_cast<double>(x - lastPos.x);

		double length = std::sqrt(dx * dx + dy * dy);
		
		//calc normal vector
		float normX = dx / length;
		float normY = dy / length;

		sf::Vector2f cursorPos{ static_cast<float>(x), static_cast<float>(y) };

		for (size_t i = 0; i < length; i++)
		{
			paint_radius(cursorPos.x, cursorPos.y);

			//move by normal vector to the desired location
			cursorPos -= {normX, normY};
		}

		lastPos = sf::Vector2i{ x, y };
	}
	
	
}

void PaintTool::onMouseRelease()
{
	state ^= BIT(0);
}

void PaintTool::paint_radius(int PosX, int PosY)
{
	// square drawing
	/*for (size_t i = 0; i < size; i++)
	{
		for (size_t z = 0; z < size; z++)
		{
			canvas->changePixel(x + z, y + i);
			canvas->changePixel(x + z, y - i);

			canvas->changePixel(x - z, y + i);
			canvas->changePixel(x - z, y - i);
		}
	}*/

	//circle drawing
	for (int y = -size; y <= size; y++)
	{
		for (int x = -size; x <= size; x++)
		{
			int actualX = PosX + x;
			int actualY = PosY + y;

			int dx = PosX - actualX;
			int dy = PosY - actualY;

			if (std::sqrt(dx * dx + dy * dy) <= size)
			{
				canvas->changePixel(
					actualX,
					actualY
				);
			}
		}
	}

}

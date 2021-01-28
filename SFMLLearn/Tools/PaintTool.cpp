#include "../Core.h"
#include "PaintTool.h"

#include <cmath>
#include <chrono>


PaintTool::PaintTool(Canvas* canvas, Options* opt) noexcept
	:Tool{ canvas }, state{ 0 },
	generator{ static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) },
	distribution{ 0, 1000 },
	options{ opt }
{}

void PaintTool::onMouseClick(float x, float y)
{
	state = BIT(0);

	paint_radius(x, y);

	lastPos = sf::Vector2f{ x, y };
}

void PaintTool::onMouseMoved(float x, float y)
{
	if ((state & BIT(0)) > (char)0)
	{


		float dy = y - lastPos.y;
		float dx = x - lastPos.x;

		float length = std::sqrt(dx * dx + dy * dy);

		//calc normal vector
		float normX = dx / length;
		float normY = dy / length;

		sf::Vector2f cursorPos{ x, y };

		for (size_t i = 0; i < length; i++)
		{
			paint_radius(cursorPos.x, cursorPos.y);

			//move by normal vector to the desired location
			cursorPos -= {normX, normY};
		}

		lastPos = sf::Vector2f{ x, y };
	}


}

void PaintTool::onMouseRelease()
{
	state ^= BIT(0);
}

void PaintTool::paint_radius(float PosX, float PosY)
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

	//circle drawing as a spray paint tool
	for (float y = -options->size; y <= options->size; y++)
	{
		for (float x = -options->size; x <= options->size; x++)
		{
			int fill_chance = distribution(generator);

			float actualX = PosX + x;
			float actualY = PosY + y;

			float dx = PosX - actualX;
			float dy = PosY - actualY;

			//basically you go in all directions and check if the point is within the radius length 
			if (fill_chance > options->fill_change && std::sqrt(dx * dx + dy * dy) <= options->size)
			{
				canvas->changePixel(
					static_cast<int>(actualX),
					static_cast<int>(actualY)
				);
			}
		}
	}

}

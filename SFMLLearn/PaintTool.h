#pragma once
#include "Tool.h"
#include <vector>

#define BIT(x) 1 << x

class PaintTool : public virtual Tool
{
	char state = 0;

	sf::Vector2i lastPos;
	uint8_t size = 10;
public:
	PaintTool() = delete;
	explicit PaintTool(Canvas* canvas) noexcept;

	void onMouseClick(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseRelease() override;

	void set_size(uint8_t new_size) { size = new_size; }

private:
	void paint_radius(int x, int y);
};

#pragma once
#include "Tool.h"
#include <vector>

#define BIT(x) 1 << x

class PaintTool : public virtual Tool
{
	char state = 0;

	sf::Vector2i lastPos;

public:
	PaintTool() = delete;
	explicit PaintTool(Canvas* canvas) noexcept;

	void onMouseClick(int x, int y) override;
	virtual void onMouseMoved(int x, int y) override;
	virtual void onMouseRelease() override;
};

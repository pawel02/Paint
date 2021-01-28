#pragma once
#include "Tool.h"
#include <random>
#include "../Options.h"

class PaintTool : public virtual Tool
{
	char state = 0;

	sf::Vector2f lastPos;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	Options* options = nullptr;
public:
	PaintTool() = delete;
	explicit PaintTool(Canvas* canvas, Options* opt) noexcept;

	void onMouseClick(float x, float y) override;
	void onMouseMoved(float x, float y) override;
	void onMouseRelease() override;

private:
	void paint_radius(float x, float y);
};

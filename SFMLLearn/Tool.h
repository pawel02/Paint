#pragma once
#include <SFML/Graphics.hpp>
#include "Canvas.h"
/*
This just defines some events that you can subscribe to or not
*/
class Tool
{
protected:
	Canvas* canvas;

public:
	explicit Tool() noexcept
		:canvas{nullptr}
	{}

	explicit Tool(Canvas* canvas_ptr) noexcept
		:canvas{ canvas_ptr}
	{}

	virtual ~Tool() noexcept {}

	//all of the events
	virtual void onMouseClick(int x, int y) {}
	virtual void onMouseMoved(int x, int y) {}
	virtual void onMouseRelease() {}

};
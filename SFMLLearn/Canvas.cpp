#include "Canvas.h"

Canvas::Canvas(float width = 800.0f, float height = 600.0f,
	float offsetX = 0.0f, float offsetY = 0.0f,
	sf::Color defaultColor = sf::Color(0.0f, 0.0f, 0.0f),
	sf::Color draw_color = sf::Color(0.0f, 0.0f, 0.0f)) noexcept

	:offsetX{ offsetX }, offsetY{offsetY},width{width}, 
	height{ height }, m_rectangle({ width, height }),
	default_color{defaultColor}

{
	m_image.create(width, height, default_color);

	m_texture.loadFromImage(m_image);
	m_rectangle.setTexture(&m_texture);
	m_rectangle.setPosition(offsetX, offsetY);
}

void Canvas::changePixel(int x, int y)
{
	//check to make sure that you are within bounds
	if (x < 0 || y < 0 || x > width - 1 || y > height - 1)
		return;

	m_image.setPixel(x, y, draw_color);
}

void Canvas::Update(sf::RenderWindow& window)
{
	m_texture.loadFromImage(m_image);
	window.draw(m_rectangle);
}
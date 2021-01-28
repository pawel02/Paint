#include "Canvas.h"

Canvas::Canvas() noexcept
	:offsetX{ 0.0f }, offsetY{ 0.0f }, width{ 800.0f },
	height{ 600.0f }, m_rectangle({ 800.0f, 600.0f }),
	default_color{ sf::Color::White },
	draw_color{ sf::Color::Black }
{
	init();
}

Canvas::Canvas(float width, float height,
	float offsetX, float offsetY,
	sf::Color defaultColor,
	sf::Color draw_color) noexcept

	:offsetX{ offsetX }, offsetY{offsetY},width{width}, 
	height{ height }, m_rectangle({ width, height }),
	default_color{defaultColor},
	draw_color{draw_color}

{
	init();
}

void Canvas::init() 
{
	m_image.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height), default_color);

	m_texture.loadFromImage(m_image);
	m_rectangle.setTexture(&m_texture);
	m_rectangle.setPosition(offsetX, offsetY);
}

void Canvas::clear()
{
	m_image.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height), default_color);
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
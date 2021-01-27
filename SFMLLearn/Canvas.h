#pragma once
#include <SFML/Graphics.hpp>

class Canvas
{
	float offsetX;
	float offsetY;

	float width;
	float height;

	//esentially I am creating a rectangle with a texture that I update 
	//this is way faster that drawing entities onto the screen
	sf::Texture m_texture;
	sf::RectangleShape m_rectangle;
	sf::Image m_image;

	sf::Color default_color;

	sf::Color draw_color;
public:

	explicit Canvas(float width, float height, 
		float offsetX, float offsetY, 
		sf::Color defaultColor,
		sf::Color draw_color) noexcept;

	~Canvas() = default;

	void changePixel(int x, int y);

	void setDrawColor(sf::Color new_color) { draw_color = new_color; }

	void Update(sf::RenderWindow& window);
};
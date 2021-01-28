#include <SFML/Graphics.hpp>

#include "./Tools/PaintTool.h"
#include "Canvas.h"

#include <memory>

int main()
{
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)), "Paint");

    //limit to 60fps for now
    window.setFramerateLimit(60);


    Canvas canvas{ windowWidth, windowHeight, 0, 0, sf::Color::White, sf::Color::Black };

    Options opt{ 10, 900 };
    std::unique_ptr<Tool> t = std::make_unique<PaintTool>(&canvas, &opt);

    // Process events
    sf::Event event;

    // Start the game loop
    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            // Pass all the events to the tools
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                t->onMouseClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                break;
            }
            case sf::Event::MouseMoved:
            {
                t->onMouseMoved(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                t->onMouseRelease();
                break;
            }
            case sf::Event::KeyPressed:
            {
                canvas.clear();
                break;
            }
            default:
                break;
            }
        }
        // Clear screen
        window.clear();

        canvas.Update(window);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
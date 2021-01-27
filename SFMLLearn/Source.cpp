#include <SFML/Graphics.hpp>

#include "PaintTool.h"
#include "Canvas.h"

#include <memory>

int main()
{
    float windowWidth = 800.0f;
    float windowHeight = 600.0f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");
    window.setFramerateLimit(60.0f);


    Canvas canvas{ windowWidth, windowHeight, 0, 0, sf::Color::White, sf::Color::Black };

    std::unique_ptr<Tool> t = std::make_unique<PaintTool>(&canvas);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
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
                t->onMouseClick(event.mouseButton.x, event.mouseButton.y);
                break;
            }
            case sf::Event::MouseMoved:
            {
                t->onMouseMoved(event.mouseMove.x, event.mouseMove.y);
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
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    // Window Object

    unsigned int window_width = 800;
    unsigned int window_height = 600;

    sf::RenderWindow window(sf::VideoMode({window_width, window_height}),
                            "Render Window",
                            sf::Style::Default,
                            sf::State::Windowed);

    // Window Configuration
    window.setFramerateLimit(30);

    sf::ContextSettings settings = window.getSettings();
    std::cout << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    // Event Handles
    const auto onClose = [&window](sf::Event::Closed)
    {
        std::cout << "Window was closed" << std::endl;
        window.close();
    };


    float radius = 10.f;
    sf::CircleShape shape1(radius);
    shape1.setOrigin({radius, radius});
    shape1.setPosition({window_width/2.f, window_height/2.f});
    shape1.setFillColor(sf::Color::Red);

    float size = 200;
    sf::RectangleShape shape2({size, size});
    shape2.setOrigin({size / 2, size / 2});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({window_width / 2.f, window_height / 2.f});
    // Event Loop
    int deg = 0;
    while (window.isOpen())
    {
        // window.handleEvents(onClose);

        while (const std::optional<sf::Event> event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // clear window with color black.
        window.clear(sf::Color::Black);

        if (deg >= 360)
        {
            deg = 0;
        }
        shape2.setRotation(sf::degrees(deg));
        // draw everything here
        window.draw(shape2);
        window.draw(shape1);

        // end the current frame
        window.display();
        deg+=2;
    }

    return 0;
}
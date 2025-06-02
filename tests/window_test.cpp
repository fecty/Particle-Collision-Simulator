#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    sf::Window window(sf::VideoMode({400, 400}), // window of size 800x600
                      "My Window",               // set title of window
                      //   sf::Style::Titlebar | sf::Style::Close, // Window styles
                      sf::Style::Default,
                      sf::State::Windowed); // use full screen

    // std::cout << window.getSize().x << "," << window.getSize().y << std::endl;
    // window.setPosition({0, 0});
    // window.setMaximumSize(sf::Vector2u({500, 500}));

    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    // run the program as long as window is open.
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // init-statements in if and while
            // Run loop as long as event is not std::nullopt.

            auto [width, height] = window.getSize(); // structured binding
            std::cout << "Size: (" << width << "," << height << ")" << std::endl;

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
    };

    return 0;
}
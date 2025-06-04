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

    window.setMinimumSize(std::optional<sf::Vector2u>({400, 300}));

    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
    };

    const auto onKeyPressed = [&window](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
        {
            window.close();
            std::cout << "the escape key was pressed" << std::endl;
            std::cout << "scancode: " << static_cast<int>(keyPressed.scancode) << std::endl;
            std::cout << "code: " << static_cast<int>(keyPressed.code) << std::endl;
            std::cout << "control: " << keyPressed.control << std::endl;
            std::cout << "alt: " << keyPressed.alt << std::endl;
            std::cout << "shift: " << keyPressed.shift << std::endl;
            std::cout << "system: " << keyPressed.system << std::endl;
            std::cout << "description: " << sf::Keyboard::getDescription(keyPressed.scancode).toAnsiString() << std::endl;
            std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed.scancode)) << std::endl;
            std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed.code)) << std::endl;
        }
    };

    const auto onResize = [&window](const sf::Event::Resized &newSize)
    {
        auto [width, height] = newSize.size;
        std::cout << "Width: " << width << " | Height: " << height << std::endl;
    };

    const auto textEntered = [&window](const sf::Event::TextEntered &text)
    {
        if (text.unicode < 128)
        {
            std::cout << static_cast<char>(text.unicode) << std::endl;
        }
    };

    // run the program as long as window is open.
    while (window.isOpen())
    {
        window.handleEvents(onClose, onKeyPressed, onResize, textEntered);

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (const auto mouse = event->getIf<sf::Event::MouseMoved>())
            {
                auto [x, y] = mouse->position;
                std::cout << x << "," << y << std::endl;
            }
        }

        // while (const std::optional event = window.pollEvent())
        // {
        //     // init-statements in if and while
        //     // Run loop as long as event is not std::nullopt.

        //     // auto [width, height] = window.getSize(); // structured binding
        //     // std::cout << "Size: (" << width << "," << height << ")" << std::endl;

        //     if (event->is<sf::Event::Closed>())
        //     {
        //         window.close();
        //     }
        //     else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        //     {

        //         if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        //         {
        //             window.close();
        //         }
        //     }
        // }
    };

    return 0;
}
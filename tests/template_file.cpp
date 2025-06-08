#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMELIMIT 30

int main()
{

    // Window Object
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Template File",
                            sf::Style::Titlebar | sf::Style::Close,
                            sf::State::Windowed);
    // Window Configuration
    window.setFramerateLimit(FRAMELIMIT);
    // Event Handling
    auto const onClose = [&window](sf::Event::Closed)
    {
        window.close();
    };
    // Main loop
    while (window.isOpen())
    {

        window.handleEvents(onClose);
        // Clearing Window
        window.clear(sf::Color::Black);
        // Drawing stuff

        // Displaying to Window
        window.display();
    }
    return 0;
}
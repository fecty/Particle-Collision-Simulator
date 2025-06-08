#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMELIMIT 30

int main()
{

    // Window Object
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Font Test",
                            sf::Style::Titlebar | sf::Style::Close,
                            sf::State::Windowed);

    // Window Configuration
    window.setFramerateLimit(FRAMELIMIT);

    // Event Handling
    auto const onClose = [&window](sf::Event::Closed)
    {
        window.close();
    };

    sf::Font font("assets\\OpenSans.ttf");

    sf::Text text(font);
    text.setString("Hello World");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition({400, 300});

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Main loop
    while (window.isOpen())
    {

        window.handleEvents(onClose);

        // Clearing Window
        window.clear(sf::Color({255, 253, 208}));

        // Drawing stuff
        window.draw(text);

        // Displaying to Window
        window.display();
    }
    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

// Main Constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FRAMERATE 30
#define BG_COLOR sf::Color::Black

#define PARTICLE_RADIUS 4.f
#define PARTICLE_COLOR sf::Color::Red
#define PARTICLE_POINT_COUNT 10
#define PARTICLE_NUMBER 100
#define SPEED_FACTOR 3

sf::Color colors[10] = {
    sf::Color(255, 99, 71),   // Tomato Red
    sf::Color(255, 165, 0),   // Orange
    sf::Color(255, 215, 0),   // Gold
    sf::Color(154, 205, 50),  // Yellow-Green
    sf::Color(0, 191, 255),   // Deep Sky Blue
    sf::Color(100, 149, 237), // Cornflower Blue
    sf::Color(123, 104, 238), // Medium Slate Blue
    sf::Color(218, 112, 214), // Orchid
    sf::Color(255, 182, 193), // Light Pink
    sf::Color(210, 180, 140)  // Tan
};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dist(0.0, 1.0);
std::uniform_int_distribution<> distX(0, WINDOW_WIDTH);
std::uniform_int_distribution<> distY(0, WINDOW_HEIGHT);

main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Window Object
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Particle Collision Simulator",
                            sf::Style::Close | sf::Style::Titlebar,
                            sf::State::Windowed,
                            settings);

    // Window Configuration
    window.setFramerateLimit(FRAMERATE);

    // User Definitions
    sf::Font font("assets\\OpenSans.ttf");

    sf::CircleShape particles[PARTICLE_NUMBER];

    float particleX, particleY;
    particleX = particleY = 0;

    std::pair<short, short> particleDir[PARTICLE_NUMBER];
    float randNum;

    for (int i = 0; i < PARTICLE_NUMBER; i++)
    {
        particles[i].setRadius(PARTICLE_RADIUS);
        particles[i].setPointCount(PARTICLE_POINT_COUNT);
        particles[i].setOrigin({PARTICLE_RADIUS, PARTICLE_RADIUS});
        particles[i].setFillColor(colors[static_cast<int>(floor(dist(gen) * 10))]);
        particles[i].setPosition({static_cast<float>(distX(gen)), static_cast<float>(distY(gen))});
        randNum = dist(gen);

        if (0 < randNum < .25)
        {
            particleDir[i].first = +1+(dist(gen)*SPEED_FACTOR);
            particleDir[i].second = +1+(dist(gen)*SPEED_FACTOR);
        }
        else if (.25 < randNum < .50)
        {
            particleDir[i].first = -1-(dist(gen)*SPEED_FACTOR);
            particleDir[i].second = +1+(dist(gen)*SPEED_FACTOR);
        }
        else if (.50 < randNum < .75)
        {
            particleDir[i].first = -1-(dist(gen)*SPEED_FACTOR);
            particleDir[i].second = -1-(dist(gen)*SPEED_FACTOR);
        }
        else if (.75 < randNum < 1.0)
        {
            particleDir[i].first = +1+(dist(gen)*SPEED_FACTOR);
            particleDir[i].second = -1-(dist(gen)*SPEED_FACTOR);
        }
        else
        {
            particleDir[i].first = +(dist(gen)*SPEED_FACTOR);
            particleDir[i].second = +(dist(gen)*SPEED_FACTOR);
        }
    }

    // Event handling
    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
        std::cout << "Window closed" << std::endl;
    };

    // Keyboard Events
    const auto onKeyPressed = [&window](const sf::Event::KeyPressed &keyPressed)
    {
        // Press W
        if (keyPressed.scancode == sf::Keyboard::Scancode::W)
        {
            std::cout << "W Pressed" << std::endl;
            return;
        }
        // Press S
        else if (keyPressed.scancode == sf::Keyboard::Scancode::S)
        {
            std::cout << "S Pressed" << std::endl;
            return;
        };
    };

    // Mouse Events
    const auto onMouseClicked = [&window](const sf::Event::MouseButtonPressed &mouse)
    {
        // Left Click
        if (mouse.button == sf::Mouse::Button::Left)
        {
            const auto [x, y] = mouse.position;
            std::cout << "Left Click: (" << x << "," << y << ")" << std::endl;

            // particle.setPosition({(float)x, (float)y});
        }
        // Right Click
        else if (mouse.button == sf::Mouse::Button::Right)
        {
            const auto [x, y] = mouse.position;
            std::cout << "Right Click: (" << x << "," << y << ")" << std::endl;
        }
    };

    // Main loop
    while (window.isOpen())
    {
        window.handleEvents(onClose, onKeyPressed, onMouseClicked);

        // Clear Window
        window.clear(BG_COLOR);

        // Draw Stuff

        for (int i = 0; i < PARTICLE_NUMBER; i++)
        {

            particleX = particles[i].getPosition().x;
            particleY = particles[i].getPosition().y;

            if (particleX > WINDOW_WIDTH)
            {
                particleX = 0;
                particleDir[i].first = -particleDir[i].first;
            }
            else if (particleX < 0)
            {
                particleX = WINDOW_WIDTH;
                particleDir[i].first = -particleDir[i].first;
            }
            else if (particleY > WINDOW_HEIGHT)
            {
                particleY = WINDOW_HEIGHT;
                particleDir[i].second = -particleDir[i].second;
            }
            else if (particleY < 0)
            {
                particleY = 0;
                particleDir[i].second = -particleDir[i].second;
            }

            particles[i].move({static_cast<float>(particleDir[i].first), static_cast<float>(particleDir[i].second)});
            window.draw(particles[i]);
        }

        // Display to window
        window.display();
    }
}
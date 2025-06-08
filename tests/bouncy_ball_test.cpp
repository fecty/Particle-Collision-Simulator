#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FRAMERATE 60

#define INITIAL_SPEEDX 0
#define INITIAL_SPEEDY 0
#define BALL_SCALE .15f
#define BALL_TEXTURE_FILE "assets\\ball.png"
#define FONT_FILE "assets\\OpenSans.ttf"

main()
{

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Bouncy Ball",
                            sf::Style::Close | sf::Style::Titlebar,
                            sf::State::Windowed);

    // Window Configuration
    window.setFramerateLimit(FRAMERATE);

    sf::Font font(FONT_FILE);

    sf::Texture ballTexture(BALL_TEXTURE_FILE);
    ballTexture.setSmooth(true);
    sf::Sprite ballSprite(ballTexture);
    auto [ballWidth, ballHeight] = ballTexture.getSize();
    ballSprite.setOrigin({ballWidth / 2.f, ballHeight / 2.f});
    ballSprite.setPosition({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    ballSprite.scale({BALL_SCALE, BALL_SCALE});
    short ballDirX = 1;
    short ballDirY = 1;
    float ballSpeedX = INITIAL_SPEEDX;
    float ballSpeedY = INITIAL_SPEEDY;
    double speedMag = 0;

    sf::Text speedText(font);
    speedText.setString("speed: ");
    speedText.setFillColor(sf::Color::Black);
    speedText.setCharacterSize(20);
    speedText.setStyle(sf::Text::Bold);
    speedText.setPosition({0, 0});
    // speedText.setOutlineThickness(2.f);
    // speedText.setOutlineColor(sf::Color::Red);

    // Events
    const auto onClose = [&window](sf::Event::Closed)
    {
        window.close();
    };

    const auto onKeyPressed = [&window, &ballSpeedX, &ballSpeedY, &ballSprite](sf::Event::KeyPressed keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Up)
        {
            ballSpeedY -= .2;
            return;
        }
        else if (keyPressed.scancode == sf::Keyboard::Scancode::Down)
        {
            ballSpeedY += .2;
            return;
        }

        else if (keyPressed.scancode == sf::Keyboard::Scancode::Right)
        {
            ballSpeedX += .2;
            return;
        }
        else if (keyPressed.scancode == sf::Keyboard::Scancode::Left)
        {
            ballSpeedX -= .2;
            return;
        }
        else if (keyPressed.scancode == sf::Keyboard::Scancode::R && keyPressed.shift)
        {
            ballSpeedX = 0;
            ballSpeedY = 0;
            ballSprite.setPosition({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
            ballSprite.setRotation(sf::degrees(0));
            return;
        }
        else if (keyPressed.scancode == sf::Keyboard::Scancode::R)
        {
            ballSpeedX = 0;
            ballSpeedY = 0;
            return;
        }
        else if (keyPressed.scancode == sf::Keyboard::Scancode::P)
        {
            ballSpeedX += 2.5;
            ballSpeedY += 2.5;
            return;
        }

        std::cout << "SpeedX: " << ballSpeedX << " | SpeedY: " << ballSpeedY << std::endl;
    };

    sf::Clock clock;
    // Main loop
    while (window.isOpen())
    {
        float t = clock.getElapsedTime().asSeconds();
        // std::cout << "Main loop Time: " << std::setprecision(3) << t << std::endl;
        window.handleEvents(onClose, onKeyPressed);

        // Clearing window
        window.clear(sf::Color::White);

        auto [ballX, ballY] = ballSprite.getPosition();
        // std::cout << "Ball Pos - X: " << ballX << " | " << "Y: " << ballY << std::endl;

        if (ballX > WINDOW_WIDTH - (ballWidth * BALL_SCALE) / 2.f || ballX < 0 + (ballWidth * BALL_SCALE) / 2.f)
        {
            // ballX = 0;
            ballDirX = -ballDirX;
            ballSprite.rotate(sf::degrees(90));
        }
        else if (ballY > WINDOW_HEIGHT - (ballHeight * BALL_SCALE) / 2.f || ballY < 0 + (ballHeight * BALL_SCALE) / 2.f)
        {
            ballDirY = -ballDirY;
            ballSprite.rotate(sf::degrees(90));
        }

        ballSprite.setPosition({ballX + ballDirX * ballSpeedX, ballY + ballDirY * ballSpeedY});

        // Alter speedText

        speedMag = round(sqrt(pow(ballSpeedX, 2) + pow(ballSpeedY, 2)));

        speedText.setString("speed(x): " + std::to_string(ballSpeedX) + "\nspeed(y): " + std::to_string(ballSpeedY));
        // Draw Stuff
        window.draw(ballSprite);
        window.draw(speedText);

        // Display to window
        window.display();
    }
    return 0;
}

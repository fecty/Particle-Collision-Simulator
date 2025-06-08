#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define FRAMELIMIT 30
#define BG_COLOR sf::Color::White

#define CHARGE_SIZE 10.f
#define CHARGE_DEFINITION 50 // Point Count
#define POS_CHARGE_COLOR sf::Color::Red 
#define NEG_CHARGE_COLOR sf::Color::Blue

#define CHARGE_K 400
#define CHARGE_A_MAG 100
#define CHARGE_B_MAG -100
#define CHARGE_A_MASS 1000
#define CHARGE_B_MASS 1

float forceE(float r, double k = CHARGE_K, double qA = CHARGE_A_MAG, double qB = CHARGE_B_MAG)
{
    return (k * qA * qB) / (r * r);
}

void assignColor(sf::CircleShape &charge, short sign)
{
    if (sign > 0)
    {
        charge.setFillColor(POS_CHARGE_COLOR);
    }
    else
    {
        charge.setFillColor(NEG_CHARGE_COLOR);
    }
};

int main()
{

    // Window Object
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Two Electrostatic Charges",
                            sf::Style::Titlebar | sf::Style::Close,
                            sf::State::Windowed);
    // Window Configuration
    window.setFramerateLimit(FRAMELIMIT);
    // Event Handling
    auto const onClose = [&window](sf::Event::Closed)
    {
        window.close();
    };

    // User Definitions
    sf::CircleShape chargeA(CHARGE_SIZE, CHARGE_DEFINITION);
    chargeA.setOrigin({CHARGE_SIZE, CHARGE_SIZE});
    assignColor(chargeA, CHARGE_A_MAG);

    sf::CircleShape chargeB(CHARGE_SIZE, CHARGE_DEFINITION);
    chargeB.setOrigin({CHARGE_SIZE, CHARGE_SIZE});
    assignColor(chargeB, CHARGE_B_MAG);

    chargeA.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    chargeB.setPosition({WINDOW_WIDTH - 100, 200});

    sf::Vector2f posChargeA(chargeA.getPosition());
    sf::Vector2f posChargeB(chargeB.getPosition());

    float angleChargeA = posChargeA.angle().asRadians();
    float angleChargeB = posChargeB.angle().asRadians();

    float r = sqrt(pow(posChargeA.x - posChargeB.x, 2) + pow(posChargeA.y - posChargeB.y, 2));

    sf::Vector2f rA({static_cast<float>(posChargeA.x * cos(angleChargeA)),
                     static_cast<float>(posChargeA.y * sin(angleChargeA))});

    sf::Vector2f rB({static_cast<float>(posChargeB.x * cos(angleChargeB)),
                     static_cast<float>(posChargeB.y * sin(angleChargeB))});

    sf::Vector2f rAB = rA - rB;
    sf::Vector2f rBA = rB - rA;

    float F = forceE(r);

    sf::Vector2f velA(sf::Vector2f({0, // Initial Vel
                                    0}));

    sf::Vector2f velB(sf::Vector2f({-80, // Initial Vel
                                    0}));

    // Clock
    sf::Clock clock;
    float t = 0;
    float prev_t = 0;
    float dt = 0;

    // Main loop
    while (window.isOpen())
    {

        t = clock.getElapsedTime().asSeconds();
        dt = t - prev_t;
        prev_t = t;
        r = sqrt(pow(posChargeA.x - posChargeB.x, 2) + pow(posChargeA.y - posChargeB.y, 2));

        if (r < CHARGE_SIZE + 30)
        {
            r = CHARGE_SIZE + 1000;
        };
        F = forceE(r);

        posChargeA = chargeA.getPosition();
        posChargeB = chargeB.getPosition();
        angleChargeA = posChargeA.angle().asRadians();
        angleChargeB = posChargeB.angle().asRadians();

        rA = sf::Vector2f({static_cast<float>(posChargeA.x * cos(angleChargeA)),
                           static_cast<float>(posChargeA.y * sin(angleChargeA))});

        rB = sf::Vector2f({static_cast<float>(posChargeB.x * cos(angleChargeB)),
                           static_cast<float>(posChargeB.y * sin(angleChargeB))});

        rAB = rA - rB;
        rBA = rB - rA;

        // Calculate force direction
        sf::Vector2f forceDirectionA = rAB / r;
        sf::Vector2f forceDirectionB = rBA / r;

        // Calculate acceleration
        sf::Vector2f accA = (F / CHARGE_A_MASS) * forceDirectionA;
        sf::Vector2f accB = (F / CHARGE_B_MASS) * forceDirectionB;

        // Update velocity
        velA += accA * dt;
        velB += accB * dt;

        window.handleEvents(onClose);

        // Clearing Window
        window.clear(BG_COLOR);

        // User Actions

        std::cout << "rAB: (" << rAB.x << ", " << rAB.y << ")  "
                  << "rBA: (" << rBA.x << ", " << rBA.y << ")  "
                  << "r: " << r << "  "
                  << "F: " << F << std::endl;

        // Update position
        chargeA.setPosition(posChargeA + velA * dt);
        chargeB.setPosition(posChargeB + velB * dt);

        // Drawing stuff
        window.draw(chargeA);
        window.draw(chargeB);

        // Displaying to Window
        window.display();
    }
    return 0;
}
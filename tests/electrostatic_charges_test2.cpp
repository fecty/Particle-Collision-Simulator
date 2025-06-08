#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define FRAMELIMIT 60
#define BG_COLOR sf::Color::White

#define A_RADIUS 30.f
#define B_RADIUS 10.f
#define PT_COUNT 50

#define POS_COLOR sf::Color::Red
#define NEG_COLOR sf::Color::Blue
#define NEUTRAL_COLOR sf::Color::Yellow

#define K 1000
#define Q_A 1
#define Q_B -1
#define M_A 1000
#define M_B 1

#define A_X 500.f // Initial X value for A
#define A_Y 400.f // Initial Y value for A
#define B_X 800.f // Initial X value for B
#define B_Y 600.f // Initial Y value for B

#define A_VX 0.f     // Initial Velocity value in X direction for A
#define A_VY 0.f     // Initial Velocity value in Y direction for A
#define B_VX -400.f // Initial Velocity value in X direction for B
#define B_VY 0.f     // Initial Velocity value in Y direction for B
#define DAMPEN_FACTOR .999f

void assignColor(sf::CircleShape &shape, int mag);
int main()
{

    // Context settings

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Window Object
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Two Electrostatic Charges",
                            sf::Style::Titlebar | sf::Style::Close,
                            sf::State::Windowed,
                            settings);

    // Window Configuration
    window.setFramerateLimit(FRAMELIMIT);

    // User Definitions
    sf::CircleShape A(A_RADIUS, PT_COUNT);
    A.setOrigin({A_RADIUS, A_RADIUS});
    A.setPosition({A_X, A_Y});
    assignColor(A, Q_A);

    sf::Vector2f initialPosA = sf::Vector2f({A_X, A_Y});
    sf::Vector2f initialVelA = sf::Vector2f({A_VX, A_VY});

    sf::CircleShape B(B_RADIUS, PT_COUNT);
    B.setOrigin({B_RADIUS, B_RADIUS});
    B.setPosition({B_X, B_Y});
    assignColor(B, Q_B);

    sf::Vector2f initialPosB = sf::Vector2f({B_X, B_Y});
    sf::Vector2f initialVelB = sf::Vector2f({B_VX, B_VY});

    sf::Vector2f r_BA = sf::Vector2f({initialPosB.x - initialPosA.x, initialPosB.y - initialPosA.y});
    sf::Vector2f r_AB = sf::Vector2f({initialPosA.x - initialPosB.x, initialPosA.y - initialPosB.y});

    float r = r_BA.length(); // or r_AB.length(). Both are same numerically

    sf::Vector2f F_AB = sf::Vector2f({(K * Q_A * Q_B) / pow((initialPosA.x - initialPosB.x), 2),
                                      (K * Q_A * Q_B) / pow((initialPosA.y - initialPosB.y), 2)});

    sf::Vector2f F_BA = sf::Vector2f({(K * Q_A * Q_B) / pow((initialPosB.x - initialPosA.x), 2),
                                      (K * Q_A * Q_B) / pow((initialPosB.y - initialPosA.y), 2)});

    sf::Vector2f a_A = sf::Vector2f({F_AB.x / M_A,
                                     F_AB.y / M_A});
    sf::Vector2f a_B = sf::Vector2f({F_BA.x / M_B,
                                     F_BA.y / M_B});

    sf::Vector2f v_A = initialVelA;
    sf::Vector2f v_B = initialVelB;

    sf::Vector2f s_A = initialPosA;
    sf::Vector2f s_B = initialPosB;

    float maxForce = K * Q_A * Q_B / (A_RADIUS + B_RADIUS);

    // Event Handling
    auto const onClose = [&window](sf::Event::Closed)
    {
        window.close();
    };

    // Mouse Events
    const auto onMouseClicked = [&](const sf::Event::MouseButtonPressed &mouse)
    {
        const auto [x, y] = mouse.position;

        // Left Click
        if (mouse.button == sf::Mouse::Button::Left)
        {
            std::cout << "Left Click: (" << x << "," << y << ")" << std::endl;
            A.setPosition({static_cast<float>(x), static_cast<float>(y)});
            initialPosA = sf::Vector2f({x, y});
            initialVelA = sf::Vector2f({0, 0});
        }
        // Right Click
        else if (mouse.button == sf::Mouse::Button::Right)
        {
            std::cout << "Right Click: (" << x << "," << y << ")" << std::endl;
            B.setPosition({static_cast<float>(x), static_cast<float>(y)});
            initialPosB = sf::Vector2f({x, y});
            initialVelB = sf::Vector2f({0, 0});
        }
    };
    const auto onMouseMoved = [&window](const sf::Event::MouseMoved &mouseMoved)
    {
        auto [x, y] = mouseMoved.position;
        std::cout << "Mouse Pos: (" << x << "," << y << ")" << std::endl;
    };

    // Clock
    sf::Clock clock;
    float t = 0;
    float prev_t = 0;
    float dt = 0;

    // Main loop
    while (window.isOpen())
    {
        // Assign new values
        t = clock.getElapsedTime().asSeconds();
        dt = t - prev_t;
        prev_t = t;

        s_A = A.getPosition();
        s_B = B.getPosition();

        r_BA = sf::Vector2f({s_B.x - s_A.x, s_B.y - s_A.y});
        r_AB = sf::Vector2f({s_A.x - s_B.x, s_A.y - s_B.y});

        float r = r_BA.length(); // or r_AB.length(). Both are same numerically

        F_AB = sf::Vector2f({(K * Q_A * Q_B * r_AB.normalized().x) / r * r,
                             (K * Q_A * Q_B * r_AB.normalized().y) / r * r});
        F_BA = sf::Vector2f({(K * Q_A * Q_B * r_BA.normalized().x) / r * r,
                             (K * Q_A * Q_B * r_BA.normalized().y) / r * r});

        if (r < A_RADIUS + B_RADIUS)
        {
            float angleA = F_AB.angle().asRadians();
            float angleB = F_BA.angle().asRadians();

            F_AB = F_AB.normalized().componentWiseMul({maxForce * cos(angleA), maxForce * sin(angleA)});
            F_BA = F_BA.normalized().componentWiseMul({maxForce * cos(angleB), maxForce * sin(angleB)});
            v_A = v_A.componentWiseMul({0, 0});
            v_B = v_B.componentWiseMul({0, 0});
            initialVelA = initialVelA.componentWiseMul({0, 0});
            initialVelB = initialVelB.componentWiseMul({0, 0});
        }
        a_A = sf::Vector2f({F_AB.x / M_A,
                            F_AB.y / M_A});
        a_B = sf::Vector2f({F_BA.x / M_B,
                            F_BA.y / M_B});

        v_A = sf::Vector2f({((a_A.x * dt) / M_A) + initialVelA.x,
                            ((a_A.y * dt) / M_A) + initialVelA.y});

        v_B = sf::Vector2f({((a_B.x * dt) / M_B) + initialVelB.x,
                            ((a_B.y * dt) / M_B) + initialVelB.y});

        s_A = sf::Vector2f({((a_A.x / 2) * dt * dt) + (initialVelA.x * dt) + (initialPosA.x),
                            ((a_A.y / 2) * dt * dt) + (initialVelA.y * dt) + (initialPosA.y)});

        s_B = sf::Vector2f({((a_B.x / 2) * dt * dt) + (initialVelB.x * dt) + (initialPosB.x),
                            ((a_B.y / 2) * dt * dt) + (initialVelB.y * dt) + (initialPosB.y)});

        initialVelA = v_A.componentWiseMul({DAMPEN_FACTOR, DAMPEN_FACTOR});
        initialVelB = v_B.componentWiseMul({DAMPEN_FACTOR, DAMPEN_FACTOR});
        initialPosA = s_A;
        initialPosB = s_B;

        
        // std::cout << F_AB.length() << " | " << F_BA.length()<< "|"<<F_AB.dot(F_BA) << std::endl;

        // Clearing Window
        window.clear(BG_COLOR);

        // Event Handler
        window.handleEvents(onClose,
                            onMouseClicked);

        // User Actions
        A.setPosition(s_A);
        B.setPosition(s_B);

        // Drawing stuff
        window.draw(A);
        window.draw(B);

        // Displaying to Window
        window.display();
    }
    return 0;
}

// Helper functions
void assignColor(sf::CircleShape &shape, int mag)
{

    if (mag < 0)
    {
        shape.setFillColor(NEG_COLOR);
    }
    else if (mag > 0)
    {
        shape.setFillColor(POS_COLOR);
    }
    else
    {
        shape.setFillColor(NEUTRAL_COLOR);
    }
}
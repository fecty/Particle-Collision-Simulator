#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <optional>

constexpr unsigned int WIDTH = 1280;
constexpr unsigned int HEIGHT = 720;
constexpr int INITIAL_NUM_BOIDS = 10;

constexpr float MAX_SPEED = 2.0f;
constexpr float MAX_FORCE = 0.05f;
constexpr float NEIGHBOR_RADIUS = 70.0f;
constexpr float SEPARATION_RADIUS = 10.0f;
constexpr float OBSTACLE_RADIUS = 30.0f;

// Utility function to limit the magnitude of a vector
sf::Vector2f limit(const sf::Vector2f &vec, float max)
{
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (mag > max)
    {
        return vec / mag * max;
    }
    return vec;
}

// Utility function to calculate distance between two vectors
float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return std::hypot(a.x - b.x, a.y - b.y);
}

// Define flock colors
const std::vector<sf::Color> flockColors = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Cyan};

class Boid
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::CircleShape shape;
    int flockID;

    Boid(float x, float y, int id) : flockID(id)
    {
        position = sf::Vector2f(x, y);
        velocity = sf::Vector2f(static_cast<float>(std::rand() % 200 - 100) / 100.f,
                                static_cast<float>(std::rand() % 200 - 100) / 100.f);
        acceleration = sf::Vector2f(0.f, 0.f);

        shape.setRadius(4.f);
        shape.setFillColor(flockColors[flockID % flockColors.size()]);
        shape.setOrigin({4.f, 4.f});
        shape.setPosition(position);
    }

    void applyForce(const sf::Vector2f &force)
    {
        acceleration += force;
    }

    void update()
    {
        velocity += acceleration;
        velocity = limit(velocity, MAX_SPEED);
        position += velocity;
        acceleration *= 0.f;

        // Wrap around screen edges
        if (position.x < 0)
            position.x += WIDTH;
        if (position.y < 0)
            position.y += HEIGHT;
        if (position.x > WIDTH)
            position.x -= WIDTH;
        if (position.y > HEIGHT)
            position.y -= HEIGHT;

        shape.setPosition(position);
        float angle = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159f;
        shape.setRotation(sf::degrees(angle));
    }

    void flock(const std::vector<Boid> &boids, const sf::Vector2f &obstaclePos)
    {
        sf::Vector2f alignment(0.f, 0.f);
        sf::Vector2f cohesion(0.f, 0.f);
        sf::Vector2f separation(0.f, 0.f);
        int total = 0;

        for (const auto &other : boids)
        {
            if (other.flockID != this->flockID)
                continue;
            float d = distance(position, other.position);
            if (&other != this && d < NEIGHBOR_RADIUS)
            {
                alignment += other.velocity;
                cohesion += other.position;

                if (d < SEPARATION_RADIUS)
                {
                    separation -= (other.position - position) / d;
                }
                total++;
            }
        }

        if (total > 0)
        {
            alignment = limit(alignment / static_cast<float>(total), MAX_FORCE);
            cohesion = limit((cohesion / static_cast<float>(total) - position), MAX_FORCE);
            separation = limit(separation / static_cast<float>(total), MAX_FORCE);

            applyForce(alignment * 1.0f);
            applyForce(cohesion * 0.8f);
            applyForce(separation * 1.5f);
        }

        // Obstacle avoidance
        float d = distance(position, obstaclePos);
        if (d < OBSTACLE_RADIUS + 20.0f)
        {
            sf::Vector2f avoidDir = position - obstaclePos;
            avoidDir = limit(avoidDir / d, MAX_FORCE);
            applyForce(avoidDir * 2.0f);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids Simulation - SFML 3.0");
    window.setVerticalSyncEnabled(true);

    std::vector<Boid> boids;
    for (int i = 0; i < INITIAL_NUM_BOIDS; ++i)
    {
        float x = static_cast<float>(std::rand() % WIDTH);
        float y = static_cast<float>(std::rand() % HEIGHT);
        int id = std::rand() % flockColors.size();
        boids.emplace_back(x, y, id);
    }

    sf::Vector2f obstaclePos(WIDTH / 2.0f, HEIGHT / 2.0f);
    sf::CircleShape obstacle(OBSTACLE_RADIUS);
    obstacle.setFillColor(sf::Color(100, 100, 100, 200));
    obstacle.setOrigin({OBSTACLE_RADIUS, OBSTACLE_RADIUS});
    obstacle.setPosition(obstaclePos);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (auto const key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Equal)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        float x = static_cast<float>(std::rand() % WIDTH);
                        float y = static_cast<float>(std::rand() % HEIGHT);
                        int id = std::rand() % flockColors.size();
                        boids.emplace_back(x, y, id);
                    }
                }
                else if (key->scancode == sf::Keyboard::Scancode::Hyphen)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (!boids.empty())
                        {
                            boids.pop_back();
                        }
                    }
                }
            }
            else if (auto const mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseButton->position.x, mouseButton->position.y});
                    int id = std::rand() % flockColors.size();
                    boids.emplace_back(mousePos.x, mousePos.y, id);
                }
                else if (mouseButton->button == sf::Mouse::Button::Right)
                {
                    obstaclePos = window.mapPixelToCoords({mouseButton->position.x, mouseButton->position.y});
                    obstacle.setPosition(obstaclePos);
                }
            }
        }

        window.clear(sf::Color::Black);

        for (auto &boid : boids)
        {
            boid.flock(boids, obstaclePos);
            boid.update();
            boid.draw(window);
        }

        window.draw(obstacle);
        window.display();
    }

    return 0;
}

#include <SFML/System.hpp>
#include <iostream>

int main()
{
    sf::Time t1 = sf::microseconds(10000);
    sf::Time t2 = sf::milliseconds(10);
    sf::Time t3 = sf::seconds(0.01);

    std::cout << "T1: " << t1.asSeconds() << std::endl;

    sf::Clock clock;

    for (int i = 0; i < 10000000000; i++)
    {
    };
    sf::Time elapsed1 = clock.getElapsedTime();
    std::cout << "Elapsed Time: " << elapsed1.asMicroseconds() << std::endl;
    std::cout << "Elapsed Time: " << elapsed1.asSeconds() << std::endl;

    clock.stop();
    clock.reset();

    clock.restart(); // This function puts the time counter back to zero,
    //                  returns the elapsed time, and leaves the clock in a running state.

    return 0;
}
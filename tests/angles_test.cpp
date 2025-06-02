#include <SFML/System.hpp>
#include <iostream>

int main()
{
    using namespace sf::Literals;

    sf::Angle angle1 = sf::degrees(180);
    sf::Angle angle2 = sf::degrees(3.1415 / 2.0);
    auto angle3 = angle1 + 45_deg;

    sf::Angle angle4 = angle2 * 2.f + angle1;

    std::cout << "Angle 1: " << angle1.asRadians() << std::endl;
    std::cout << "Angle 2: " << angle2.asDegrees() << std::endl;
    std::cout << "Angle 3: " << angle3.asDegrees() << std::endl;
    std::cout << "Angle 4: " << angle4.asDegrees() << std::endl;

    return 0;
}
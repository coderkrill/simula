#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "random/perlin.hpp"
#include "random/random.hpp"
#include "quad.hpp"
#include "world.hpp"

int main()
{
    sf::Texture cat_texture;
    cat_texture.loadFromFile("kat.jpeg");
    sf::Image cat_image = cat_texture.copyToImage();
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(30);
    window.setIcon(184, 183, cat_image.getPixelsPtr());

    World world({200,200});

    while (window.isOpen())
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition();
        sf::Vector2i window_pos = window.getPosition();
        sf::Vector2i pos = mouse_pos - window_pos;
        //std::cout << pos.x << " " << pos.y << "\n";
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        world.update();

        window.clear();
        window.draw(world);
        window.display();
    }

    return 0;
}

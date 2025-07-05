#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Input {
public:
    Input(float x, float y);  
    void setImage(const std::vector<uint8_t>& pixels); // 28x28 grayscale
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    

private:
    sf::Vector2f position;
    std::vector<sf::RectangleShape> blocks;  
    sf::RectangleShape border;               
};

#include "Input.h"

// Constructor: initializes the input display area at (x, y).
// A 280x280 square is drawn to represent the 28x28 pixel image.
Input::Input(float x, float y) : position(x, y) {
    border.setPosition(position);
    border.setSize(sf::Vector2f(280.f, 280.f));
    border.setFillColor(sf::Color::Transparent);  
    border.setOutlineColor(sf::Color::Black); // visual border 
    border.setOutlineThickness(5.f);
}

// Sets the image to be displayed based on 28x28 grayscale pixel values.
// If already initialized, only updates block colors to avoid re-creating shapes.
void Input::setImage(const std::vector<uint8_t>& pixels)
{
    const float blockSize = 10.f;

    // If blocks already exist, just update their color (faster).
    if (blocks.size() == 784) {
        for (unsigned i = 0; i < 784; ++i) {
            uint8_t inverted = 255 - pixels[i];
            blocks[i].setFillColor(sf::Color(inverted, inverted, inverted));
        }
        return;
    }

    // First-time initialization: create and position blocks.
    blocks.clear();

    for (unsigned row = 0; row < 28; ++row) {
        for (unsigned col = 0; col < 28; ++col) {
            uint8_t gray = pixels[row * 28 + col];
            uint8_t inverted = 255 - gray;

            sf::RectangleShape pixelBlock(sf::Vector2f(blockSize, blockSize));
            pixelBlock.setFillColor(sf::Color(inverted, inverted, inverted));
            pixelBlock.setPosition(position.x + col * blockSize, position.y + row * blockSize);

            blocks.push_back(pixelBlock);
        }
    }
}


void Input::draw(sf::RenderWindow& window)
{
    window.draw(border);
    for (const auto& block : blocks)
        window.draw(block);  
}

sf::Vector2f Input::getPosition()
{
    return position;
}
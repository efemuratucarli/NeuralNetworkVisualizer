#include "Button.h"
#include "Layer.h"
#include <iostream>
using namespace std;

Button::Button(int posx, int posy, int width, int height, sf::String label, Type type)
{
	font.loadFromFile("../assets/font.ttf");
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(20);
	rect.setPosition((float)posx, (float)posy);
	rect.setSize(sf::Vector2f((float)width, (float)height));
	rect.setFillColor(sf::Color(0, 255, 0, 255));
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	text.setPosition(posx + width / 2, posy + height / 2);
	this->m_type = type; //m_type is the button type
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	sf::FloatRect r = rect.getGlobalBounds();
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return r.contains(mousePos);

}

void Button::onPressed(Network& layerList)
{
	if (this->m_type == addLayer)
	{
		layerList.addLayer(100, 400);
	}
}

void Button::onPressed(Layer& layer)
{
	if (this->m_type == addNeuron)
	{
		layer.addNeuron();
	}
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}

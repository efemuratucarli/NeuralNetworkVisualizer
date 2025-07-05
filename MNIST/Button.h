#pragma once
#include <SFML/Graphics.hpp>
#include "Network.h"

class Button {
public:
	enum Type
	{
		addLayer,
		addNeuron,
		build,
		train,
		test,
	};
private:
	sf::Font font;
	sf::RectangleShape rect;
	sf::Text text;
	Type m_type;
public:
	Button(int posx, int posy, int width, int height, sf::String label, Type type);
	bool isMouseOver(sf::RenderWindow&);
	void onPressed(Network& layerList);
	void onPressed(Layer& layer);
	void draw(sf::RenderWindow&);
};
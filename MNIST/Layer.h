#pragma once
#include <SFML/Graphics.hpp>
#include "Neuron.h"

class Layer
{
public:
	Layer(int numberOfLayers, int width = 100, int height = 200);
	void draw(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow&);
	void toggleSelection();
	bool getSelection(); 
	void addNeuron();
	int getNeuronCount() const;
	sf::Vector2f getNeuronPosition(int index) const;
	std::vector<Neuron>& getNeurons();

	// Sadece okuma eriþimi için:
	const std::vector<Neuron>& getNeurons() const;

	std::vector<float> getOutputs() const;

private:
	sf::RectangleShape rect;
	int initialPosX = 350;
	int initialPosY = 50;
	bool isSelected = false;
	std::vector<Neuron> neurons;  
	int neuronSpacing = 30;      
};

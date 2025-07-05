#include "Layer.h"
#include <iostream>
using namespace std;

// Constructor: Sets position and size of the layer box based on its index.
// Helps align layers horizontally with spacing between them.
Layer::Layer(int numberOfLayers, int width, int height)
{
	int currentPosX, currentPosY;
	int offset = 50;
	if (numberOfLayers == 0)
	{
		currentPosX = this->initialPosX;
	}
	else
	{
		currentPosX = this->initialPosX + (numberOfLayers*(width + offset));
	}
	currentPosY = this->initialPosY;
	rect.setPosition((float)currentPosX, (float)currentPosY);
	rect.setSize(sf::Vector2f((float)width, (float)height));
	rect.setFillColor(sf::Color(0, 255, 0, 255));
}

void Layer::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	for (Neuron& neuron : neurons)
		neuron.draw(window);
}

// Checks if the mouse is currently hovering over this layer.
// Used for layer selection via clicking.
bool Layer::isMouseOver(sf::RenderWindow& window)
{
	sf::FloatRect r = rect.getGlobalBounds();
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return r.contains(mousePos);
}

// Toggles the selection state of the layer.
// Visually highlights the layer when selected.
void Layer::toggleSelection()
{
	isSelected = !isSelected;  

	if (isSelected)
	{
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(6.f);
	}
	else
	{
		rect.setOutlineThickness(0.f);
	}
}

bool Layer::getSelection()
{
	return this->isSelected;
}

// Adds a new neuron to the layer.
// Automatically positions the neuron based on spacing and layer location.
void Layer::addNeuron()
{
	float radius = 6.f;
	float spacing = (float)neuronSpacing;

	sf::Vector2f layerPos = rect.getPosition();
	float layerWidth = rect.getSize().x;

	float centerX = layerPos.x + (layerWidth / 2.f) - radius;
	float posY = layerPos.y + neurons.size() * spacing;

	neurons.emplace_back(centerX, posY, radius);
}

int Layer::getNeuronCount() const
{
	return neurons.size();
}

sf::Vector2f Layer::getNeuronPosition(int index) const
{
	return neurons[index].getPosition();
}

std::vector<Neuron>& Layer::getNeurons() {
	return neurons;
}

const std::vector<Neuron>& Layer::getNeurons() const {
	return neurons;
}

// Collects and returns the output values of all neurons in this layer.
// Used as input to the next layer during forward propagation.
std::vector<float> Layer::getOutputs() const {
	std::vector<float> outputs;
	for (const Neuron& neuron : this->getNeurons()) {
		outputs.push_back(neuron.getOutput());
	}
	return outputs;
}
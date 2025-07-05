#pragma once
#include <SFML/Graphics.hpp>
class Neuron
{
public:
	Neuron(float x, float y, float radius);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;
	void initializeWeights(int inputSize);
	float getBias();
	void setBias(float);
	std::vector<float>& getWeights();
	float getOutput() const;
	float getGradient() const;
	void setOutput(float output);
	void setGradient(float gradient);
	const std::vector<float>& getWeights() const;
private:
	sf::CircleShape shape;
	std::vector<float> weights;
	float bias;
	float output;
	float gradient;
};
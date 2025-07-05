#include "Neuron.h"
#include <iostream>
#include <random>   
using namespace std;
Neuron::Neuron(float x, float y, float radius) : output(0.0f), gradient(0.0f)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);
    bias = 2.0f * (rand() / static_cast<float>(RAND_MAX)) - 1.0f;
}

void Neuron::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2f Neuron::getPosition() const
{
    return shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
}

void Neuron::initializeWeights(int inputSize)
{
    weights.resize(inputSize);
    for (auto& w : weights)
        w = 2.0f * (rand() / static_cast<float>(RAND_MAX)) - 1.0f;
}

std::vector<float>& Neuron::getWeights() {
    return weights;
}

const std::vector<float>& Neuron::getWeights() const {
    return weights;
}

float Neuron::getBias()
{
    return this->bias;
}

void Neuron::setBias(float bias)
{
    this->bias = bias;
}

float Neuron::getOutput() const
{
    return this->output;
}

float Neuron::getGradient() const
{
    return this->gradient;
}

void Neuron::setOutput(float output)
{
    this->output = output;
    return;
}

void Neuron::setGradient(float gradient)
{
    this->gradient = gradient;
    return;
}
#pragma once
#include <vector>
#include "Layer.h"
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Activation.h"

// Training Constants
constexpr float LEARNING_RATE = 0.01f;
constexpr int NUM_EPOCHS = 20;

class Network {
public:
    Network();
    void addLayer(float width = 200, float height = 200); 
    void draw(sf::RenderWindow& window);
    bool isEmpty();
    int size();
    Layer& operator[](int i);
    void buildConnections(); 
    void trainNetwork(Input&, sf::RenderWindow& window);
    Layer& back();
    void testNetwork();

private:
    std::vector<Layer> layers;
    static int numberOfLayers;
    std::vector<sf::VertexArray> connections;  
    bool isNetworkBuilt;
    bool isNetworkTrained;
    void initializeWeights();
    std::vector<float> forward(std::vector<float> input);
    void backpropagate(const std::vector<float>& probs, int trueLabel);
    void updateWeights(const std::vector<float>& inputs, float learningRate);
};
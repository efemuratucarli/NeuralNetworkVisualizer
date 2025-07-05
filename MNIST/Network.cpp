#include "Network.h"
#include "DatasetLoader.h"
#include <iostream>
using namespace std;

Network::Network()
{
    isNetworkTrained = false;
    isNetworkBuilt = false;
}

// Adds a new layer to the network and increments the global layer count.
// Layers are indexed in insertion order.
void Network::addLayer(float width, float height) {
    layers.emplace_back(numberOfLayers, width, height);
    numberOfLayers++;
}

// Renders all layers and their connecting lines to the window.
// This function is used to visualize the network structure.
void Network::draw(sf::RenderWindow& window) {
    for (Layer& layer : layers)
        layer.draw(window);
    
    for (const auto& line : connections)
        window.draw(line);
}

bool Network::isEmpty()
{
    return layers.empty();
}

int Network::size()
{
    return numberOfLayers;
}

Layer& Network::operator[](int i)
{
    return layers[i];
}

// Builds the connection lines between neurons of adjacent layers.
// Also marks the network as built so training can be allowed.
void Network::buildConnections()
{
    connections.clear();

    for (size_t i = 0; i + 1 < layers.size(); ++i)
    {
        const Layer& left = layers[i];
        Layer& right = layers[i + 1];

        for (size_t a = 0; a < left.getNeuronCount(); ++a)
        {
            for (size_t b = 0; b < right.getNeuronCount(); ++b)
            {
                sf::VertexArray line(sf::Lines, 2);
                line[0].position = left.getNeuronPosition(a);
                line[0].color = sf::Color::Blue;
                line[1].position = right.getNeuronPosition(b);
                line[1].color = sf::Color::Blue;
                connections.push_back(line);
            }
        }
    }
    isNetworkBuilt = true;
}

// Initializes the weights of each neuron depending on its input size.
// Input size is determined by the size of the previous layer or 784 for the input layer.
void Network::initializeWeights()
{
    for (size_t i = 0; i < this->size(); ++i)
    {
        Layer& right = (*this)[i];
        int inputSize = (i == 0) ? 784 : static_cast<int>((*this)[i - 1].getNeuronCount());
        for (auto& neuron : right.getNeurons()) {
            neuron.initializeWeights(inputSize);
        }
    }
}

// Performs a forward pass over the network.
// ReLU is used for hidden layers and softmax is applied to the output layer.
std::vector<float> Network::forward(std::vector<float> input)
{
    for (size_t l = 0; l < this->size(); ++l) {
        std::vector<float> newInput;

        for (Neuron& neuron : (*this)[l].getNeurons()) {
            float sum = neuron.getBias();
            const std::vector<float>& weights = neuron.getWeights();
            for (size_t w = 0; w < weights.size(); ++w) {
                sum += input[w] * weights[w];
            }

            float activated = (l == this->size() - 1)
                ? sum
                : std::max(0.0f, sum); // ReLU
            neuron.setOutput(activated);
            newInput.push_back(activated);
        }

        input = newInput;
    }

    // Only the output layer uses softmax to produce class probabilities
    Layer& outputLayer = this->back();
    std::vector<float> logits;
    for (Neuron& neuron : outputLayer.getNeurons()) {
        logits.push_back(neuron.getOutput());
    }

    std::vector<float> probs = softmax(logits);
    for (size_t k = 0; k < outputLayer.getNeuronCount(); ++k) {
        outputLayer.getNeurons()[k].setOutput(probs[k]);
    }

    return probs;
}

// Computes gradients for all neurons using backpropagation.
// Uses the derivative of cross-entropy with softmax for the output layer.
void Network::backpropagate(const std::vector<float>& probs, int trueLabel)
{
    // Output layer
    Layer& outputLayer = this->back();
    for (size_t k = 0; k < outputLayer.getNeuronCount(); ++k) {
        Neuron& neuron = outputLayer.getNeurons()[k];
        float target = (k == trueLabel) ? 1.0f : 0.0f;
        neuron.setGradient(neuron.getOutput() - target);
    }

    // Hidden layers
    for (int l = static_cast<int>(this->size()) - 2; l >= 0; --l) {
        Layer& curr = (*this)[l];
        Layer& next = (*this)[l + 1];

        for (size_t j = 0; j < curr.getNeuronCount(); ++j) {
            Neuron& neuron = curr.getNeurons()[j];
            float gradSum = 0.0f;

            for (Neuron& nextNeuron : next.getNeurons()) {
                gradSum += nextNeuron.getWeights()[j] * nextNeuron.getGradient();
            }

            neuron.setGradient((neuron.getOutput() > 0.0f) ? gradSum : 0.0f);
        }
    }
}

// Updates weights and biases using gradient descent.
// Learning rate determines the step size.
void Network::updateWeights(const std::vector<float>& inputs, float learningRate)
{
    for (size_t l = 0; l < this->size(); ++l) {
        const std::vector<float>& inputVec = (l == 0) ? inputs : (*this)[l - 1].getOutputs();

        for (Neuron& neuron : (*this)[l].getNeurons()) {
            std::vector<float>& weights = neuron.getWeights();
            for (size_t j = 0; j < weights.size(); ++j) {
                weights[j] -= learningRate * neuron.getGradient() * inputVec[j];
            }
            neuron.setBias(neuron.getBias() - learningRate * neuron.getGradient());
        }
    }
}

// Trains the network only if it is properly built and has 10 neurons in the output layer (required for MNIST)
void Network::trainNetwork(Input& inputDisplay, sf::RenderWindow& window)
{
    if (isNetworkBuilt && !layers.empty() && layers.back().getNeuronCount() == 10)
    {
        std::vector<std::vector<float>> images;
        std::vector<int> labels;

        loadDataset("../assets/mnist_data_train.csv", images, labels);
        std::cout << "Training set sample count: " << images.size() << std::endl;

        this->initializeWeights();

        // 2. Training loop
        for (int epoch = 0; epoch < NUM_EPOCHS; ++epoch) {

            float totalLoss = 0.0f;
            int correct = 0;

            for (size_t i = 0; i < images.size(); ++i) {
                std::vector<float> input = images[i];

                // Update the GUI to reflect the current input image
                std::vector<uint8_t> grayPixels;
                for (float val : images[i])
                    grayPixels.push_back(static_cast<uint8_t>(val * 255));

                inputDisplay.setImage(grayPixels);
                
                // Clear the display area and redraw the image
                sf::RectangleShape clearBox(sf::Vector2f(280.f, 280.f));
                clearBox.setPosition(inputDisplay.getPosition());  
                clearBox.setFillColor(sf::Color::White);
                window.draw(clearBox);
                inputDisplay.draw(window);
                window.display();

                //// Forward-pass
                std::vector<float> probs = forward(input);
                int predictedClass = std::max_element(probs.begin(), probs.end()) - probs.begin();
                int trueLabel = labels[i];

                if (predictedClass == trueLabel)
                    correct++;

                // === Loss ===
                float y = probs[trueLabel];
                float loss = -std::log(std::max(y, 1e-7f));
                totalLoss += loss;

                //// Backpropagation
                this->backpropagate(probs, trueLabel);
                //// Weight & bias update
                this->updateWeights(input, LEARNING_RATE);
            }

            float accuracy = static_cast<float>(correct) / images.size();
            std::cout << "[Epoch " << epoch + 1 << "] Avg loss = "
                << totalLoss / images.size()
                << ", Accuracy = " << accuracy * 100.0f << "%\n";
        }

        isNetworkTrained = true;
    }
    else{
        std::cout << "Training aborted: Network must be built and last layer must have 10 neurons." << std::endl;
    }
    
    return;
}

Layer& Network::back()
{
    return layers.back();
}

void Network::testNetwork()
{
    if (isNetworkTrained)
    {
        std::vector<std::vector<float>> images;
        std::vector<int> labels;

        loadDataset("../assets/mnist_data_test.csv", images, labels);
        std::cout << "Test set sample count: " << images.size() << std::endl;
        int correct = 0;
        float totalLoss = 0.0;

        for (size_t i = 0; i < images.size(); ++i) {
            std::vector<float> input = images[i];

            //// Forward-pass
            std::vector<float> probs = forward(input);

            int predictedClass = std::max_element(probs.begin(), probs.end()) - probs.begin();
            int trueLabel = labels[i];

            if (predictedClass == trueLabel)
                correct++;

            // === Loss ===
            float y = probs[trueLabel];
            float loss = -std::log(std::max(y, 1e-7f));
            totalLoss += loss;
        }
        float accuracy = static_cast<float>(correct) / images.size();
        std::cout << "Avg loss = "
            << totalLoss / images.size()
            << ", Test Accuracy = " << accuracy * 100.0f << "%\n";
    }
    else
    {

    }
    return;
}

int Network::numberOfLayers = 0;
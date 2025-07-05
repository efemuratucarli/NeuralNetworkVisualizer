#include "DatasetLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Loads a CSV-formatted MNIST dataset.
// Each line starts with a label (0-9), followed by 784 pixel values.
// Normalized pixel values are stored as floats in [0,1] range.
void loadDataset(const char* filename,
    std::vector<std::vector<float>>& images,
    std::vector<int>& labels)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::vector<float> image;
        int label;

        std::stringstream ss(line);
        std::string token;

        getline(ss, token, ',');
        label = std::stoi(token);

        while (getline(ss, token, ',')) {
            float pixel = std::stof(token) / 255.0f;
            image.push_back(pixel);
        }

        if (image.size() == 784) {
            labels.push_back(label);
            images.push_back(image);
        }
    }

    file.close();
}
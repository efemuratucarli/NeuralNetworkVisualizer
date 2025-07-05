#include "Activation.h"
#include <cmath>
std::vector<float> softmax(const std::vector<float>& z)
{
    std::vector<float> result(z.size());
    float maxVal = *std::max_element(z.begin(), z.end());
    float sum = 0.0f;

    for (size_t i = 0; i < z.size(); ++i) {
        result[i] = std::exp(z[i] - maxVal);
        sum += result[i];
    }

    for (float& val : result) val /= sum;
    return result;
}
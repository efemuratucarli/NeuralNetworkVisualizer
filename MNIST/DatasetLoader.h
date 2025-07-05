#pragma once
#include <vector>
#include <string>

void loadDataset(const char* filename,
    std::vector<std::vector<float>>& images,
    std::vector<int>& labels);
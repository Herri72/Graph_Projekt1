#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SchiebePuzzle {
private:
    std::vector<std::vector<int>> matrix;

public:
    explicit SchiebePuzzle(const std::vector<std::string> &eingabe);

    static std::pair<int, int> leeresFeld (const std::vector<std::vector<int>> &puzzle);

    static std::vector<std::vector<std::vector<int>>> getNeighbors(const std::vector<std::vector<int>> &puzzle);
};
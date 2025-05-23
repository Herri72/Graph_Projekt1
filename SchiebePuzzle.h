#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class SchiebePuzzle {
private:
    std::vector<std::vector<int>> matrix;

public:
    explicit SchiebePuzzle(const std::vector<std::string> &eingabe);

    [[nodiscard]] bool istLösbar () const;

    [[nodiscard]] std::pair<int, int> leeresFeld () const;

    std::vector<std::vector<std::vector<int>>> getNeighbors();
};
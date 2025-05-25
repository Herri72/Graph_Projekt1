#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

class SchiebePuzzle {
private:


    std::vector<std::vector<int>> matrix;

public:
    SchiebePuzzle(const vector<std::vector<int>> &initial_matrix);

    explicit SchiebePuzzle(const std::vector<std::string> &eingabe);

    [[nodiscard]] bool istLösbar () const;

    [[nodiscard]] std::pair<int, int> leeresFeld () const;

    std::vector<std::vector<std::vector<int>>> getNeighbors();

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] const std::vector<std::vector<int>>& getMatrix() const;
};

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

    SchiebePuzzle ();

    SchiebePuzzle (const SchiebePuzzle &other);

    [[nodiscard]] bool istLösbar () const;

    [[nodiscard]] std::pair<int, int> leeresFeld () const;

    void Swap (const int &zeile, const int &spalte, const int &otherZeile, const int &otherSpalte);

    static std::vector<SchiebePuzzle> getNeighbors(const SchiebePuzzle &puzzle);
};
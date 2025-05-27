#pragma once
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class SchiebePuzzle {
private:
    std::vector<std::vector<int>> matrix;

public:
    bool operator == (const SchiebePuzzle& other) const;

    explicit SchiebePuzzle(const std::vector<std::string> &eingabe);

    SchiebePuzzle ();

    SchiebePuzzle (const SchiebePuzzle &other);

    explicit SchiebePuzzle (std::vector<std::vector<int>> eingabe): matrix(std::move(eingabe)) {};

    [[nodiscard]] bool istLösbar () const;

    [[nodiscard]] std::pair<int, int> leeresFeld () const;

    void Swap (const int &zeile, const int &spalte, const int &otherZeile, const int &otherSpalte);

    static std::vector<SchiebePuzzle> getNeighbors(const SchiebePuzzle &puzzle);
};
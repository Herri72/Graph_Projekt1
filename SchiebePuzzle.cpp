#include "SchiebePuzzle.h"

SchiebePuzzle::SchiebePuzzle(const std::vector<std::string> &eingabe) {
    // Eingabe Parameter durchlaufen
    for (int i = 0; i < eingabe.size(); ++i) {
        // Wenn es eine Zahl ist, im Vector an passender Stelle einfügen
        if (!eingabe [i].empty() && std::all_of(eingabe[i].begin(), eingabe[i].end(), ::isdigit)) {
            matrix [static_cast<int>(i/3)] [i % 3] = std::stoi(eingabe [i]);
        }
        // Wenn es das e ist, im Vector an passender Stelle als 0 einfügen
        else if (eingabe [i] == "e") {
            matrix [static_cast<int>(i/3)] [i % 3] = 0;
        }
        else {
            std::cout << "Fehler: Ungültige Eingabe!" << std::endl;
        }
    }
}
SchiebePuzzle::SchiebePuzzle(const std::vector<std::vector<int>> &initial_matrix) : matrix(initial_matrix) {
    // Basic validation, can be expanded
    if (matrix.size() != 3 || (!matrix.empty() && matrix[0].size() != 3)) {
        // std::cerr << "Error: SchiebePuzzle constructed with invalid matrix dimensions." << std::endl;
        // Potentially throw an exception or set to a defined error state
        matrix.assign(3, std::vector<int>(3,0)); // Fallback to a default empty matrix
    }
}

bool SchiebePuzzle::istLösbar() const{
    std::vector<int> eindimensional;
    // wandelt das puzzle (2d Vektor) in einen 1d Vektor um
    for (const auto& row : matrix) {
        std::copy(row.begin(), row.end(), std::back_inserter(eindimensional));
    }

    // zählt wie häufig ein größer nummeriertes Puzzleteil vor einem kleiner nummerierten Puzzleteil steht (in 1d sicht gedacht)
    // dies ist als Inversion bezeichnet
    int inversionsCounter = 0;
    for (int i = 1; i < eindimensional.size(); ++i) {
        for (int j = i; j >= 0; --j) {
            if (eindimensional [j] > eindimensional[i]) {
                ++inversionsCounter;
            }
        }
    }
    // Wenn die Anzahl der Inversionen mod 2 gleich 0 ist, dann true, sonst false
    return inversionsCounter % 2 == 0;
}

std::pair<int, int> SchiebePuzzle::leeresFeld() const {
    // Durchlaufen der Zeilen und Spalten
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 0) {
                // Position des leeren Feldes zurückgeben
                return {i, j};
            }
        }
    }
    // Fehler, falls kein leeres Feld gefunden werden sollte
    std::cout << "Keine Null!" << std::endl;
    return {-1, -1};
}

std::vector<std::vector<std::vector<int>>> SchiebePuzzle::getNeighbors() {
    int zeile = leeresFeld().first;
    int spalte = leeresFeld().second;
    std::vector<std::vector<std::vector<int>>> neighbors;

    // lLinksverschiebung möglich
    if (zeile >= 1) {
        std::vector<std::vector<int>> neighbour = matrix;
        neighbour [zeile] [spalte] = matrix [zeile - 1] [spalte];
        neighbour [zeile - 1] [spalte] = matrix [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Rechtsverschiebung möglich
    if (zeile <= 1) {
        std::vector<std::vector<int>> neighbour = matrix;
        neighbour [zeile] [spalte] = matrix [zeile + 1] [spalte];
        neighbour [zeile + 1] [spalte] = matrix [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Nach oben Verschieben möglich
    if (spalte >= 1) {
        std::vector<std::vector<int>> neighbour = matrix;
        neighbour [zeile] [spalte] = matrix [zeile] [spalte - 1];
        neighbour [zeile] [spalte - 1] = matrix [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Nach unten Verschieben möglich
    if (spalte <= 1) {
        std::vector<std::vector<int>> neighbour = matrix;
        neighbour [zeile] [spalte] = matrix [zeile] [spalte + 1];
        neighbour [zeile] [spalte + 1] = matrix [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    return neighbors;
}
std::string SchiebePuzzle::toString() const {
    std::string s = "";
    s.reserve(9); // Reserve space for 9 characters
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[i][j] == 0) {
                s += 'e';
            } else {
                s += std::to_string(matrix[i][j]);
            }
        }
    }
    return s;
}

const std::vector<std::vector<int>>& SchiebePuzzle::getMatrix() const {
    return matrix;
}

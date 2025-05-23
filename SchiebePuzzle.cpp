#include "SchiebePuzzle.h"

SchiebePuzzle::SchiebePuzzle(const std::vector<std::string> &eingabe) {
    // Eingabe Parameter durchlaufen
    for (int i = 0; i < eingabe.size(); i++) {
        // Wenn es eine Zahl ist, im Vector an passender Stelle einfügen
        if (!eingabe [i].empty() && std::all_of(eingabe[i].begin(), eingabe[i].end(), ::isdigit)) {
            matrix [static_cast<int>(i/3)] [i % 3] = std::stoi(eingabe [i]);
        }
        // Wenn es das e ist, im Vector an passender Stelle als 0 einfügen
        else if (eingabe [i] == "e") {
            matrix [static_cast<int>(i/3)] [i % 3] = 0;
        }
        else {
            std::cerr << "Fehler: Ungültige Eingabe!" << std::endl;
        }
    }
}

std::pair<int, int> SchiebePuzzle::leeresFeld(const std::vector<std::vector<int> > &puzzle) {
    // Durchlaufen der Zeilen und Spalten
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            if (puzzle[i][j] == 0) {
                // Position des leeren Feldes zurückgeben
                return {i, j};
            }
        }
    }
    // Fehler, falls kein leeres Feld gefunden werden sollte
    std::cerr << "Keine Null!" << std::endl;
    return {-1, -1};
}

std::vector<std::vector<std::vector<int>>> SchiebePuzzle::getNeighbors(const std::vector<std::vector<int>> &puzzle) {
    int zeile = leeresFeld(puzzle).first;
    int spalte = leeresFeld(puzzle).second;
    std::vector<std::vector<std::vector<int>>> neighbors;

    // lLinksverschiebung möglich
    if (zeile >= 1) {
        std::vector<std::vector<int>> neighbour = puzzle;
        neighbour [zeile] [spalte] = puzzle [zeile - 1] [spalte];
        neighbour [zeile - 1] [spalte] = puzzle [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Rechtsverschiebung möglich
    if (zeile <= 1) {
        std::vector<std::vector<int>> neighbour = puzzle;
        neighbour [zeile] [spalte] = puzzle [zeile + 1] [spalte];
        neighbour [zeile + 1] [spalte] = puzzle [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Nach oben Verschieben möglich
    if (spalte >= 1) {
        std::vector<std::vector<int>> neighbour = puzzle;
        neighbour [zeile] [spalte] = puzzle [zeile] [spalte - 1];
        neighbour [zeile] [spalte - 1] = puzzle [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    // Nach unten Verschieben möglich
    if (spalte <= 1) {
        std::vector<std::vector<int>> neighbour = puzzle;
        neighbour [zeile] [spalte] = puzzle [zeile] [spalte + 1];
        neighbour [zeile] [spalte + 1] = puzzle [zeile] [spalte];
        neighbors.push_back(neighbour);
    }
    return neighbors;
}


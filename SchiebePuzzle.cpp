#include "SchiebePuzzle.h"

bool SchiebePuzzle::operator==(const SchiebePuzzle &other) const {
    if (this->matrix.size() != other.matrix.size()) {
        return false;
    }
    for (int i = 0; i < other.matrix.size(); ++i) {
        for (int j = 0; j < other.matrix [i].size(); ++j) {
            if (this->matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

SchiebePuzzle::SchiebePuzzle(const std::vector<std::string> &eingabe) {
    matrix = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
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
    //cout << "nach einlesen" << this->toString() << " " << this->matrix [0] [0];
}

SchiebePuzzle::SchiebePuzzle() = default;

SchiebePuzzle::SchiebePuzzle(const SchiebePuzzle &other) {
    matrix = other.matrix;
}

bool SchiebePuzzle::istLösbar() const{
    std::vector<int> eindimensional;
    // wandelt das puzzle (2d Vektor) in einen 1d Vektor um
    for (const auto& row : matrix) {
        std::copy(row.begin(), row.end(), std::back_inserter(eindimensional));
    }
    eindimensional.erase(
    std::remove(eindimensional.begin(), eindimensional.end(), 0),
    eindimensional.end());

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
    cout << this->toString() << matrix [0] [0];
    std::cout << "Keine Null!" << std::endl;
    cout << this->toString();
    return {-1, -1};
}

void SchiebePuzzle::Swap(const int &zeile, const int &spalte, const int &otherZeile, const int &otherSpalte) {
    int akt = this->matrix[zeile][spalte];
    this->matrix[zeile][spalte] = this->matrix[otherZeile][otherSpalte];
    this->matrix[otherZeile][otherSpalte] = akt;
}

std::vector<SchiebePuzzle> SchiebePuzzle::getNeighbors() const {
    const int zeile = this->leeresFeld().first;
    const int spalte = this->leeresFeld().second;
    std::vector<SchiebePuzzle> neighbors;

    // lLinksverschiebung möglich
    if (zeile >= 1) {
        SchiebePuzzle neighbour (*this);
        neighbour.Swap(zeile, spalte, zeile - 1, spalte);
        neighbors.push_back(neighbour);
    }
    // Rechtsverschiebung möglich
    if (zeile <= 1) {
        SchiebePuzzle neighbour (*this);
        neighbour.Swap(zeile, spalte, zeile + 1, spalte);
        neighbors.push_back(neighbour);
    }
    // Nach oben Verschieben möglich
    if (spalte >= 1) {
        SchiebePuzzle neighbour (*this);
        neighbour.Swap(zeile, spalte, zeile, spalte - 1);
        neighbors.push_back(neighbour);
    }
    // Nach unten Verschieben möglich
    if (spalte <= 1) {
        SchiebePuzzle neighbour (*this);
        neighbour.Swap(zeile, spalte, zeile, spalte + 1);
        neighbors.push_back(neighbour);
    }
    return neighbors;
}

std::string SchiebePuzzle::toString() const {
    string stringpuzzle;
    for (int i = 0; i < this->matrix.size(); ++i) {
        for (int j = 0; j < this->matrix [i].size(); ++j) {
            if (this->matrix [i] [j] == 0){
                stringpuzzle += "e ";
            }
            else {
                stringpuzzle += to_string(this->matrix[i][j]) + " ";
            }
        }
    }
    return stringpuzzle;
}

vector<int> SchiebePuzzle::toVector() const {
    std::vector<int> flat;
    for (const auto& row : matrix) {
        flat.insert(flat.end(), row.begin(), row.end());
    }
    return flat;
}

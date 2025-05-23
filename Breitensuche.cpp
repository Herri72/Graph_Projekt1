#include "Breitensuche.h"

std::string Breitensuche::Suche(const SchiebePuzzle &puzzle) {
    if (!puzzle.istLösbar()) {
        std::cout << "NO SOLUTION\n";
        return "NO SOLUTION\n";
    }

    // Queue die den vorherigen Zustand und den aktuellen Zustand des Schiebepuzzles speichert
    std::queue<std::pair <SchiebePuzzle, SchiebePuzzle>> zustände;
}


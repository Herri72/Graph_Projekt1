#include "Breitensuche.h"

std::string Breitensuche::Suche(const SchiebePuzzle &puzzle) {
    if (!puzzle.istLösbar()) {
        std::cout << "NO SOLUTION\n";
        return "NO SOLUTION\n";
    }

    // Queue die den vorherigen Zustand und den aktuellen Zustand des Schiebepuzzles speichert
    const std::vector<std::vector<int>> final_matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    const SchiebePuzzle ziel_zustand = SchiebePuzzle (final_matrix);
    std::queue<std::pair<std::vector<SchiebePuzzle>, SchiebePuzzle>> queue;
    std::map<vector<int>, short> visited;

    if (puzzle == ziel_zustand) {
        return "Solution found\n";
    }

    std::vector <SchiebePuzzle> states;
    states.push_back(puzzle);
    queue.push({states, puzzle});
    visited.emplace(puzzle.toVector(), 0);

    while (!queue.empty()) {
        SchiebePuzzle aktuellesPuzzle = queue.front().second;
        vector <SchiebePuzzle> aktuellerPfad = queue.front().first;

        vector <SchiebePuzzle> neighbours = aktuellesPuzzle.getNeighbors();
        for (int i = 0; i < neighbours.size(); ++i) {
            vector <SchiebePuzzle> newPath = aktuellerPfad;
            newPath.push_back(neighbours [i]);
            if (neighbours [i] == ziel_zustand) {
                cout << "Solution found\n";
                for (const auto & j : newPath) {
                    cout << j.toString() << "\n";
                }
                return "";
            }
            if (!visited.contains(neighbours[i].toVector())){
                queue.push({newPath, neighbours [i]});
                visited.emplace(neighbours [i].toVector(), 0);
            }
        }
    }
    return "NO SOLUTION";
}


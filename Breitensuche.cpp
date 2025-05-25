#include "Breitensuche.h"

std::string Breitensuche::Suche(const SchiebePuzzle &puzzle) {
    if (!puzzle.istLösbar()) {
        std::cout << "NO SOLUTION\n";
        return "NO SOLUTION\n";
    }

    // Queue die den vorherigen Zustand und den aktuellen Zustand des Schiebepuzzles speichert
    queue<pair <SchiebePuzzle, SchiebePuzzle>> zustände;

    const std::string ziel_zustand_str = "12345678e";
    std::queue<std::pair<SchiebePuzzle, std::string>> q;
    std::set<std::string> besucht;
    std::string start_zustand_str = puzzle.toString();

    if (start_zustand_str == ziel_zustand_str) {
        return "";
    }

    q.push({puzzle, ""});
    besucht.insert(start_zustand_str);

    const std::vector<std::tuple<int, int, char>> moves = {
            {1, 0, 'U'},
            {-1, 0, 'D'},
            {0, 1, 'L'},
            {0, -1, 'R'}
    };

    const int N = 3;

    while (!q.empty()) {
        SchiebePuzzle aktuellesPuzzle = q.front().first;
        std::string aktuellerPfad = q.front().second;
        q.pop();

        std::pair<int,int> leereFeldPos = aktuellesPuzzle.leeresFeld();
        int zeile_alt = leereFeldPos.first;  // Current row of the empty spot
        int spalte_alt = leereFeldPos.second; // Current column of the empty spot

        for(const auto& move_info : moves){
            int zeile = std::get<0>(move_info);
            int spalte = std::get<1>(move_info);
            char zug_char = std::get<2>(move_info);

            int zeile_kachel = zeile_alt + zeile;
            int spalte_kachel = spalte_alt + spalte;

            if (zeile_kachel >= 0 && zeile_kachel < N && spalte_kachel >= 0 && spalte_kachel < N) {
                std::vector<std::vector<int>> nachbar_matrix_data = puzzle.getMatrix();

                //Tausch
                nachbar_matrix_data[zeile_alt][spalte_alt] = nachbar_matrix_data[zeile_kachel][spalte_kachel];
                nachbar_matrix_data[zeile_kachel][spalte_kachel] = 0; // The tile's old spot is now empty.

                SchiebePuzzle nachbarPuzzle(nachbar_matrix_data); // Create new puzzle state.
                std::string nachbar_zustand_str = nachbarPuzzle.toString();

                if (nachbar_zustand_str == ziel_zustand_str) {
                    return aktuellerPfad + zug_char; // Solution found!
                }
                if (besucht.find(nachbar_zustand_str) == besucht.end()) {
                    besucht.insert(nachbar_zustand_str);
                    q.push({nachbarPuzzle, aktuellerPfad + zug_char});
                }
            }
        }


    }
    return "NO SOLUTION";
}


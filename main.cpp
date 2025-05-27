#include "parameter_reader.h"
#include <iostream>
#include "Breitensuche.h"

using namespace std; // wuerde ich empfehlen zu benutzen, diese Zeile kann aber auch geloescht werden
// Nach dem Loeschen dieser Zeile muss unten dann allerdings std::vector<std::string> geschrieben werden!

int main(int argc, char** argv) {


    vector<string> input_vector = input_to_vector(argc, argv); // the input given in console is now in input_vector
    // (e.g. for input "hallo 1 a b" input_vector is {"hallo", "1", "a", "b"})
    string start;
    for (const string &token: input_vector)
        start += token;
    cout<<"start" <<start << "\n";

    SchiebePuzzle puzzle_instanz(input_vector);
    std::string loesung = Breitensuche::Suche(puzzle_instanz);

    std::cout << loesung << std::endl;

    return 0;

}

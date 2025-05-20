#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include "Media.h"  // Include il tuo header

int main() {
    // Crea alcuni media
    auto media1 = std::make_shared<media::Media>(
        "House of Cards",
        2013,
        "English",
        std::vector<std::string>{"Drama", "Politics"},
        true
    );

    auto media2 = std::make_shared<media::Media>(
        "The Crown",
        2016,
        "English",
        std::vector<std::string>{"History", "Drama"},
        false
    );

    auto media3 = std::make_shared<media::Media>(
        "Breaking Bad",
        2008,
        "English",
        std::vector<std::string>{"Crime", "Thriller"},
        false
    );

    // Inserisci i media in un vettore
    std::vector<std::shared_ptr<media::Media>> inputList = {media1, media2, media3};

    // Crea un oggetto Media come filtro
    auto filterMedia = std::make_shared<media::Media>(
        "Ho",
        std::numeric_limits<int>::min(), 
        "dra"
    );
    
    // Filtra
    std::vector<std::shared_ptr<media::Media>> filtered = filterMedia->filter(inputList);

    // Stampa i risultati
    std::cout << "Media che passano il filtro:\n";
    for (const auto& m : filtered) {
        std::cout << "- " << m->getTitle() << "\n";
    }

    return 0;
}

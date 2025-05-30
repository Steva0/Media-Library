#include <QCoreApplication>
#include <QFile>
#include <iostream>

#include "Memory/Database.h"
#include "Media/Movie.h"
#include "Media/Series.h"
#include "Media/Album.h"
#include "Media/Ebook.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Step 1: Crea alcuni media
    media::Album album(
        "TitoloAlbum", 2077, "IT", false,
        {"Rock", "Synthwave"}, "", "Band pazza",
        "CyberBand", {"Membro1", "Membro2"}, {}
    );

    media::Album album2(
        "TitoloAlbum2", 2077, "IT", false,
        {"Rock", "Synthwave"}, "./img_album.jpg", "Band pazza",
        "CyberBand", {"Membro1", "Membro2"}, {"Track1", "Track2"}
    );

    media::Ebook ebook(
        "TitoloEbook", 2025, "EN", true,
        {"Fantasy", "Adventure"}
    );

    media::Ebook ebook2(
        "TitoloEbook2"
    );

    // Step 2: Crea istanze dei database
    memory::Database dbJson;
    memory::Database dbXml;

    // Step 3: Apri file
    if (!dbJson.open("output.json")) {
        std::cerr << "Errore apertura output.json\n";
        return 1;
    } else {
        std::cout << "Apertura output.json riuscita\n";

        const auto& all = dbJson.getAll();
        std::cout << "Numero elementi caricati: " << all.size() << "\n";
    }

    // Step 3: Apri file
    if (!dbXml.open("output.xml")) {
        std::cerr << "Errore apertura output.xml\n";
        return 1;
    } else {
        std::cout << "Apertura output.xml riuscita\n";

        const auto& all = dbXml.getAll();
        std::cout << "Numero elementi caricati: " << all.size() << "\n";
    }

    
    // Step 4: Aggiungi media
    dbJson.addMedia(ebook);
    dbJson.addMedia(album);
    dbJson.removeMedia(ebook2);
    dbJson.removeMedia(album2);
    //dbXml.addMedia(ebook);
    dbXml.removeMedia(ebook2);
    //dbXml.addMedia(album);
    dbXml.removeMedia(album2);


    

    // Step 5: Salva in JSON
    if (dbJson.save())
        std::cout << "Serializzazione JSON riuscita\n";
    else
        std::cerr << "Errore serializzazione JSON\n";

    // Step 6: Salva in XML
    if (dbXml.save())
        std::cout << "Serializzazione XML riuscita\n";
    else
        std::cerr << "Errore serializzazione XML\n";


    std::cout << "Chiusura dei file completata.\n";

    return 0;
}

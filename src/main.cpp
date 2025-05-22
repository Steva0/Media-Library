#include <QCoreApplication>
#include <QSaveFile>
#include <iostream>

#include "Memory/MediaContainer.h"
#include "Memory/Serializer.h"
#include "Media/Movie.h"
#include "Media/Series.h"
#include "Media/Album.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Step 1: Crea media
    media::Album album("Titolo", 2077, "IT", false, {"OMG"}, "./", "Ohoihiohoi");
    media::Ebook ebook(
            "TitoloEbook", 123123, "O.O", true,
            {"Genere1", "Genere2", "Genere3"},
            "Dobbiamo ricordarci di filtrare caratteri",
            "Notaio", "Notatu", "ZaPaburishaa", 666,
            "Ho finito le idee", "ISBNNN", -1, true);


    // Step 2: Inserisci nel container
    memory::MediaContainer container;
    container.addMedia(ebook);
    container.addMedia(album);

    // Step 3: Serializza in JSON
    {
        QSaveFile jsonFile("output.json");
        int res = container.serialize(jsonFile);
        if (res == 0)
            std::cout << "Serializzazione JSON riuscita\n";
        else
            std::cerr << "Errore serializzazione JSON: " << res << "\n";
    }

    // Step 4: Serializza in XML
    {
        QSaveFile xmlFile("output.xml");
        // Sovrascrivo momentaneamente Format in Serializer.cpp per usare XML
        int res = container.serialize(xmlFile);
        if (res == 0)
            std::cout << "Serializzazione XML riuscita\n";
        else
            std::cerr << "Errore serializzazione XML: " << res << "\n";
    }

    return 0;
}


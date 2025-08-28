#ifndef STREAMINGSERVICES_H
#define STREAMINGSERVICES_H

// L'implementazione logica non offre una lista di servizi streaming per audiolibri.
// Abbiamo deciso di definirla all'interno dell'interfaccia grafica, ritenendo che
// ciò non violi la separazione tra implementazione logica e grafica,
// immaginandola una funzionalità introdotta da un utilizzatore della libreria
// (= l'implementazione logica).
#include <QStringList>

namespace gui {
    inline const QStringList kStreamingServices{
        "Tutti", "Audible", "Audiobooks.com", "B&N Audiobooks",
        "Libro.fm", "Everand", "Spotify", "Libby", "Hoopla", "Chirp"
    };
}

#endif // STREAMINGSERVICES_H

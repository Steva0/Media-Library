#include <QFile>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "Media/Album.h"
#include "Media/Media.h"  // Include il tuo header
#include "Media/Ebook.h"
#include "Memory/MediaXMLVisitor.h"
using namespace memory;
using namespace media;

int main() {
    QFile f("album");

    f.open(QIODevice::Text | QIODevice::WriteOnly);
  {
    MediaXMLVisitor v;
    Album album("Titolo", 2077, "IT", false, {"OMG"}, "./", "Ohoihiohoi");
    album.accept(v);

    f.write(v.getDocument().toByteArray());
  }
  {
    MediaXMLVisitor v;
    Media media("NomeMedia");
    media.accept(v);

    f.write(v.getDocument().toByteArray());
  }
  {
    MediaXMLVisitor v;
    Ebook ebook("TitoloEbook", 123123, "O.O", true, {"Genere1", "Genere2", "Genere3"}, "Dobbiamo ricordarci di filtrare caratteri", "Notaio", "Notatu", "ZaPaburishaa", 666, "Ho finito le idee", "ISBNNN", -1, true);
    ebook.accept(v);
    f.write(v.getDocument().toByteArray());
  }
    f.close();
}

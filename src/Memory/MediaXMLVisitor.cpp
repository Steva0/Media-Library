#include "MediaXMLVisitor.h"

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Media.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"

namespace memory {
const QDomDocument &MediaXMLVisitor::getDocument() const { return document_; }
QDomElement MediaXMLVisitor::elementFrom(const std::string &key,
                                         const std::string &value) {
  QDomElement el = document_.createElement(QString::fromStdString(key));
  el.appendChild(document_.createTextNode(QString::fromStdString(value)));
  return el;
}
QDomElement MediaXMLVisitor::elementFrom(const std::string &key, int value) {
  QDomElement el = document_.createElement(QString::fromStdString(key));
  el.appendChild(document_.createTextNode(QString::number(value)));
  return el;
}
QDomElement MediaXMLVisitor::elementFrom(const std::string &key,
                                         unsigned int value) {
  QDomElement el = document_.createElement(QString::fromStdString(key));
  el.appendChild(document_.createTextNode(QString::number(value)));
  return el;
}
QDomElement MediaXMLVisitor::elementFrom(const std::string &empty) {
  QDomElement el;
  el.setTagName(QString::fromStdString(empty));
  return el;
}
void MediaXMLVisitor::visit(const media::Media &media) {
  if (media.getTitle().empty()) {
    return;
  }
  QDomElement base = document_.createElement("Media");
  QDomElement el;

  base.appendChild(elementFrom("Title", media.getTitle()));

  if (media.getRelease() != std::numeric_limits<int>::min())
    base.appendChild(elementFrom("Release", media.getRelease()));
  if (media.getLanguage() != "")
    base.appendChild(elementFrom("Language", media.getLanguage()));
  if (media.isFavourite())
    base.appendChild(elementFrom("Favourite"));

  if (!media.getGenres().empty()) {
    el = document_.createElement("Genres");
    for (const std::string &genre : media.getGenres()) {
      el.appendChild(elementFrom("Genre", genre));
    }
    base.appendChild(el);
  }

  if (media.getImgPath() != "")
    base.appendChild(elementFrom("ImagePath", media.getImgPath()));
  if (media.getNotes() != "")
    base.appendChild(elementFrom("Notes", media.getNotes()));

  document_.appendChild(base);
}

void MediaXMLVisitor::visit(const media::Album &album) {
  if (album.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(album));
  document_.childNodes().at(0).toElement().setTagName("Album");
  if (album.getBand() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Band", album.getBand()));
  if (!album.getBandMembers().empty()) {
    QDomElement el = document_.createElement("BandMembers");
    for (const std::string &member : album.getBandMembers()) {
      el.appendChild(elementFrom("Member", member));
    }
    document_.childNodes().at(0).toElement().appendChild(el);
  }
  if (!album.getSongs().empty()) {
    QDomElement el = document_.createElement("Songs");
    for (const std::string &song : album.getSongs()) {
      el.appendChild(elementFrom("Song", song));
    }
    document_.childNodes().at(0).toElement().appendChild(el);
  }
}

void MediaXMLVisitor::visit(const media::Movie &movie) {
  if (movie.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(movie));
  document_.childNodes().at(0).toElement().setTagName("Movie");
  if (!movie.getCast().empty()) {
    QDomElement el = document_.createElement("Cast");
    for (const std::string &act : movie.getCast()) {
      el.appendChild(elementFrom("Act", act));
    }
    document_.childNodes().at(0).toElement().appendChild(el);
  }
  if (movie.getLength() != std::numeric_limits<int>::min())
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Length", movie.getLength()));
  if (movie.getUniverse() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Universe", movie.getUniverse()));
}

void MediaXMLVisitor::visit(const media::Series &series) {
  if (series.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Movie &>(series));
  document_.childNodes().at(0).toElement().setTagName("Series");
  if (series.getEpisodes() != std::numeric_limits<int>::min())
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Episodes", series.getEpisodes()));
  if (series.getSeasons() != std::numeric_limits<int>::min())
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Seasons", series.getSeasons()));
  if (series.hasEnded())
    document_.childNodes().at(0).toElement().appendChild(elementFrom("Ended"));
}

void MediaXMLVisitor::visit(const media::Novel &novel) {
  if (novel.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(novel));
  document_.childNodes().at(0).toElement().setTagName("Novel");

  if (novel.getAuthor() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Author", novel.getAuthor()));
  if (novel.getPublisher() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Publisher", novel.getPublisher()));
  if (novel.getPages() != std::numeric_limits<int>::min())
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Pages", novel.getPages()));
  if (novel.getSeries() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Series", novel.getSeries()));
  if (novel.getIsbn() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("ISBN", novel.getIsbn()));
}

void MediaXMLVisitor::visit(const media::AudioBook &audioBook) {
  if (audioBook.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Novel &>(audioBook));
  document_.childNodes().at(0).toElement().setTagName("AudioBook");
  if (audioBook.getNarrator() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Narrator", audioBook.getNarrator()));
  if (audioBook.getStreamingService() != "")
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Service", audioBook.getStreamingService()));
}

void MediaXMLVisitor::visit(const media::Ebook &ebook) {
  if (ebook.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Novel &>(ebook));
  document_.childNodes().at(0).toElement().setTagName("Ebook");
  if (ebook.getFileSizeBytes() != std::numeric_limits<int>::min())
    document_.childNodes().at(0).toElement().appendChild(
        elementFrom("Bytes", ebook.getFileSizeBytes()));
  if (ebook.hasDrm())
    document_.childNodes().at(0).toElement().appendChild(elementFrom("DRM"));
}
}  // namespace memory

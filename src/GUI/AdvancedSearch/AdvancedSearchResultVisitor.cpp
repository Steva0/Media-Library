#include "AdvancedSearchResultVisitor.h"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

#include "../../Media/Album.h"
#include "../../Media/AudioBook.h"
#include "../../Media/Ebook.h"
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Novel.h"
#include "../../Media/Series.h"
#include "qgridlayout.h"

namespace gui {
namespace advanced_search {
void AdvancedSearchResultVisitor::visit(const media::Media &media) {
  img_ = new QPixmap(QString::fromStdString(media.getImgPath()));

  data_ = new QWidget;
  grid_ = new QGridLayout(data_);

  // bisogna sistemare i valori di default all'interno di addRow
  addRow("Titolo", media.getTitle());
  addRow("Lingua", media.getLanguage());
  addRow("Data", media.getRelease());
  addRow("Genere", media.getGenres());
  // come mettiamo il preferito?
  notes_ = new QLabel(QString::fromStdString(media.getNotes()));
}
void AdvancedSearchResultVisitor::visit(const media::Album &album) {
  visit(static_cast<const media::Media &>(album));
  addRow("Band", album.getBand());
  addRow("Members", album.getBandMembers());
  // tutta 'sta roba?
  addRow("Songs", album.getSongs());
}
void AdvancedSearchResultVisitor::visit(const media::Movie &movie) {
  visit(static_cast<const media::Media &>(movie));
  addRow("Durata", movie.getLength());
  addRow("Universo", movie.getUniverse());
  addRow("Cast", movie.getCast());
}
void AdvancedSearchResultVisitor::visit(const media::Series &series) {
  visit(static_cast<const media::Movie &>(series));
  addRow("Stagioni", series.getSeasons());
  addRow("Episodi", series.getEpisodes());
  if (series.hasEnded()) {
    addRow("Terminato");
  } else {
    addRow("Non terminato");
  }
}
void AdvancedSearchResultVisitor::visit(const media::Novel &novel) {
  visit(static_cast<const media::Media &>(novel));
  addRow("Autore", novel.getAuthor());
  addRow("Editore", novel.getPublisher());
  addRow("Serie", novel.getSeries());
  addRow("Pagine", novel.getPages());
  addRow("ISBN", novel.getIsbn());
  
}
void AdvancedSearchResultVisitor::visit(const media::AudioBook &audio_book) {
  visit(static_cast<const media::Media &>(audio_book));
  addRow("Voce", audio_book.getNarrator());
  addRow("Servizio Streaming", audio_book.getStreamingService());
}
void AdvancedSearchResultVisitor::visit(const media::Ebook &ebook) {
  visit(static_cast<const media::Media &>(ebook));
  if (ebook.hasDrm())
    addRow("DRM");
}

void AdvancedSearchResultVisitor::addRow(const std::string &key,
                                          const std::string &value) {
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                   grid_->rowCount(), 0);
  grid_->addWidget(new QLabel(QString::fromStdString(value)), grid_->rowCount(),
                   1);
}
void AdvancedSearchResultVisitor::addRow(const std::string &key, int value) {
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                    grid_->rowCount(), 0);
  grid_->addWidget(new QLabel(QString::number(value)), grid_->rowCount(), 1);
}
void AdvancedSearchResultVisitor::addRow(
    const std::string &key, const std::vector<std::string> &value) {
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                    grid_->rowCount(), 0);
  for (const std::string &v : value) {
    grid_->addWidget(new QLabel(QString::fromStdString(v)), grid_->rowCount(),
                      1);
  }
}
void AdvancedSearchResultVisitor::addRow(const std::string &only_key) {
  addRow(only_key, "");
}

}  // namespace advanced_search
}  // namespace gui

#include "ResultVisitor.h"

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

namespace gui {
namespace advanced_search {
QWidget *ResultVisitor::getResult() {
  // todo result -> wrapper
  auto *result = new QWidget;
  auto *wrapper = new QFrame(result);
  wrapper->setFrameShape(QFrame::Box);
  auto *wrapper_layout = new QHBoxLayout(wrapper);

  wrapper_layout->addWidget(img_);
  wrapper_layout->addWidget(data_);

  img_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  auto *layout = new QHBoxLayout(result);
  layout->addWidget(wrapper);

  return result;
}
void ResultVisitor::visit(const media::Media &media) {
  img_ = new QLabel;
  // img_->setPixmap(*new QPixmap(QString::fromStdString(media.getImgPath())));
  img_->setPixmap(*new QPixmap((QPixmap(":/assets/matita.jpg").scaled(128, 128))));  // debug

  data_ = new QWidget;
  grid_ = new QGridLayout(data_);

  // bisogna sistemare i valori di default all'interno di addRow
  addRow("Titolo", media.getTitle());
  // titolo in grassetto
    static_cast<QLabel *>(grid_->itemAt(0)->widget())
        ->setStyleSheet("font: bold");
    static_cast<QLabel *>(grid_->itemAt(1)->widget())
        ->setStyleSheet("font: bold");

  addRow("Lingua", media.getLanguage());
  addRow("Data", media.getRelease());
  addRow("Genere", media.getGenres());
  // come mettiamo il preferito? stella?
  notes_ = new QLabel(QString::fromStdString(media.getNotes()));
}
void ResultVisitor::visit(const media::Album &album) {
  visit(static_cast<const media::Media &>(album));
  addRow("Band", album.getBand());
  addRow("Members", album.getBandMembers());
  // tutta 'sta roba?
  addRow("Songs", album.getSongs());
}
void ResultVisitor::visit(const media::Movie &movie) {
  visit(static_cast<const media::Media &>(movie));
  addRow("Durata", movie.getLength());
  addRow("Universo", movie.getUniverse());
  addRow("Cast", movie.getCast());
}
void ResultVisitor::visit(const media::Series &series) {
  visit(static_cast<const media::Movie &>(series));
  addRow("Stagioni", series.getSeasons());
  addRow("Episodi", series.getEpisodes());
  if (series.hasEnded()) {
    addRow("Terminato");
  } else {
    addRow("Non terminato");
  }
}
void ResultVisitor::visit(const media::Novel &novel) {
  visit(static_cast<const media::Media &>(novel));
  addRow("Autore", novel.getAuthor());
  addRow("Editore", novel.getPublisher());
  addRow("Serie", novel.getSeries());
  addRow("Pagine", novel.getPages());
  addRow("ISBN", novel.getIsbn());
}
void ResultVisitor::visit(const media::AudioBook &audio_book) {
  visit(static_cast<const media::Media &>(audio_book));
  addRow("Voce", audio_book.getNarrator());
  addRow("Servizio Streaming", audio_book.getStreamingService());
}
void ResultVisitor::visit(const media::Ebook &ebook) {
  visit(static_cast<const media::Novel &>(ebook));
  if (ebook.hasDrm()) addRow("DRM");
}

void ResultVisitor::addRow(const std::string &key,
                                         const std::string &value) {
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                   grid_->rowCount(), 0);

  // l'aggiunta del widget sopra aumenta di uno il numero di righe
  grid_->addWidget(new QLabel(QString::fromStdString(value)),
                   grid_->rowCount() - 1, 1);

}
void ResultVisitor::addRow(const std::string &key, int value) {
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                   grid_->rowCount(), 0);
  grid_->addWidget(new QLabel(QString::number(value)), grid_->rowCount() - 1,
                   1);
}
void ResultVisitor::addRow(
    const std::string &key, const std::vector<std::string> &value) {
  if (value.size() == 0) {
    addRow(key, "");
    return;
  }
  grid_->addWidget(new QLabel(QString::fromStdString(key) + ":"),
                   grid_->rowCount(), 0, Qt::AlignTop);

  grid_->addWidget(new QLabel(QString::fromStdString(std::accumulate(
                       value.cbegin(), value.cend(), value[0],
                       [](const std::string &left, const std::string &right) {
                         return left + "\n" + right;
                       }))),
                   grid_->rowCount() - 1, 1);
}
void ResultVisitor::addRow(const std::string &only_key) {
  addRow(only_key, "");
}

}  // namespace advanced_search
}  // namespace gui

#include "MediaInputWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <limits>
#include "InputWidget.h"

namespace gui {
namespace advanced_search {
const int MediaInputWidget::kColumnAmount = 6;
const size_t MediaInputWidget::kMaxGenres = 3;

MediaInputWidget::MediaInputWidget(QWidget *parent) : QWidget(parent), container_(new QVBoxLayout(this)) {
  media_layout_ = new QGridLayout;

  title_ = new QLineEdit(this);
  title_->setPlaceholderText("Titolo");

  auto *release_label = new QLabel("Anno di uscita:", this);
  release_ = new QLineEdit(this);
  release_->setValidator(new QIntValidator(-1000, 1000, release_));

  auto *language_label = new QLabel("Lingua:", this);
  language_ = new QLineEdit(this);

  auto *favourite_label = new QLabel("Preferito:", this);
  favourite_ = new QCheckBox(this);

  auto *genre_label = new QLabel("Generi:", this);
  genre_input_ = new QLineEdit(this);
  auto *add_genre = new QPushButton("+", this);

  media_layout_->addWidget(title_, 0, 0, 1, kColumnAmount);

  media_layout_->addWidget(release_label);
  media_layout_->addWidget(release_);

  media_layout_->addWidget(language_label);
  media_layout_->addWidget(language_);

  media_layout_->addWidget(favourite_label);
  media_layout_->addWidget(favourite_);

  media_layout_->addWidget(genre_label);
  media_layout_->addWidget(genre_input_, media_layout_->rowCount() - 1, 1, 1, kColumnAmount - 2);
  media_layout_->addWidget(add_genre);

  container_->addLayout(media_layout_);

  connect(add_genre, &QAbstractButton::pressed, this, &MediaInputWidget::addGenre);
}

void MediaInputWidget::addGenre() {
  if (genre_input_->text() == "") return;
  if (genres_.size() == kMaxGenres) {
    return;
  }
  if (std::find_if(genres_.begin(), genres_.end(),
                   [&](QLineEdit *genre) { return genre_input_->text() == genre->text(); }) != genres_.end()) {
    genre_input_->clear();  // feedback visivo (non posso cercare due volte lo stesso genere)
    return;
  }
  auto *new_genre = new QLineEdit(genre_input_->text(), this);
  new_genre->setEnabled(false);
  genre_input_->clear();

  auto *remove_button = new QPushButton("-", this);

  media_layout_->addWidget(new_genre, media_layout_->rowCount(), 1, 1, kColumnAmount - 2);
  media_layout_->addWidget(remove_button);

  genres_.push_back(new_genre);

  connect(remove_button, &QAbstractButton::pressed, this,
          [this, new_genre, remove_button]() { removeGenre(new_genre, remove_button); });
}

void MediaInputWidget::removeGenre(QLineEdit *genre, QPushButton *button) {
  auto it = std::find(genres_.begin(), genres_.end(), genre);
  media_layout_->removeWidget(*it);
  (*it)->deleteLater();
  genres_.erase(it);
  media_layout_->removeWidget(button);
  button->deleteLater();
}
void MediaInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
  
void MediaInputWidget::setFromMedia(const media::Media &media) {
  title_->setText(QString::fromStdString(media.getTitle()));

  QString release = QString::number(media.getRelease());
  if (media.getRelease() == std::numeric_limits<int>::min()) release.clear();
  release_->setText(release);
  language_->setText(QString::fromStdString(media.getLanguage()));
  favourite_->setChecked(media.isFavourite());
  for (size_t i = 0; i < std::min<size_t>(3, media.getGenres().size()); ++i) {
    genre_input_->setText(QString::fromStdString(media.getGenres()[i]));
    addGenre();
  }
}
std::string MediaInputWidget::getTitle() const { return title_->text().toStdString(); }
bool MediaInputWidget::getFavourite() const { return favourite_->isChecked(); }
std::string MediaInputWidget::getLanguage() const { return language_->text().toStdString(); }
int MediaInputWidget::getRelease() const {
  if (release_->text() == "") return std::numeric_limits<int>::min();
  return release_->text().toInt();
}
std::vector<std::string> MediaInputWidget::getGenres() const {
  std::vector<std::string> result(genres_.size());
  for (const QLineEdit *genre: genres_) {
    result.push_back(genre->text().toStdString());
  }
  return result;
}
}  // namespace advanced_search
}  // namespace gui

#include "MediaInputWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace gui {
namespace advanced_search {
const int MediaInputWidget::kColumnAmount = 6;
const size_t MediaInputWidget::kMaxGenres = 3;

void MediaInputWidget::addWidget(QWidget *left, QWidget *right, bool half_size) {
  int span = (kColumnAmount - 1);
  if (half_size) span /= 2;
  layout_->addWidget(left);
  layout_->addWidget(right, layout_->rowCount() - 1, 1, 1, span);
}

MediaInputWidget::MediaInputWidget(QWidget *parent) : QWidget(parent) {
  layout_ = new QGridLayout(this);

  title_ = new QLineEdit(this);
  title_->setPlaceholderText("Title");

  auto *release_label = new QLabel("Release:", this);
  release_ = new QLineEdit(this);
  release_->setValidator(new QIntValidator(-5000, 5000, release_));

  auto *language_label = new QLabel("Language:", this);
  language_ = new QLineEdit(this);
  language_->setMaxLength(2);

  auto *favourite_label = new QLabel("Favourite:", this);
  favourite_ = new QCheckBox(this);

  auto *genre_label = new QLabel("Genres:", this);
  genre_input_ = new QLineEdit(this);
  auto *add_genre = new QPushButton("+", this);

  layout_->addWidget(title_, 0, 0, 1, kColumnAmount);

  layout_->addWidget(release_label);
  layout_->addWidget(release_);

  layout_->addWidget(language_label);
  layout_->addWidget(language_);

  layout_->addWidget(favourite_label);
  layout_->addWidget(favourite_);

  layout_->addWidget(genre_label);
  layout_->addWidget(genre_input_, layout_->rowCount() - 1, 1, 1, kColumnAmount - 2);
  layout_->addWidget(add_genre);

  connect(add_genre, &QAbstractButton::pressed, this, &MediaInputWidget::addGenre);
}

void MediaInputWidget::addGenre() {
  if (genre_input_->text() == "") return;
  if (genres_.size() == kMaxGenres) { return; }
  if (std::find_if(genres_.begin(), genres_.end(),
                   [&](QLineEdit *genre) { return genre_input_->text() == genre->text(); }) != genres_.end()) {
    genre_input_->clear(); // feedback visivo
    return;
  }
  auto *new_genre = new QLineEdit(genre_input_->text(), this);
  new_genre->setEnabled(false);
  genre_input_->clear();

  auto *remove_button = new QPushButton("-", this);

  layout_->addWidget(new_genre, layout_->rowCount(), 1, 1, kColumnAmount - 2);
  layout_->addWidget(remove_button);

  genres_.push_back(new_genre);

  connect(remove_button, &QAbstractButton::pressed, this,
          [this, new_genre, remove_button]() { removeGenre(new_genre, remove_button); });
}

void MediaInputWidget::removeGenre(QLineEdit *genre, QPushButton *button) {
  auto it = std::find(genres_.begin(), genres_.end(), genre);
  layout_->removeWidget(*it);
  (*it)->deleteLater();
  genres_.erase(it);
  layout_->removeWidget(button);
  button->deleteLater();
}

QString MediaInputWidget::getTitle() const { return title_->text(); }

int MediaInputWidget::getRelease() const { return release_->text().toInt(); }

QString MediaInputWidget::getLanguage() const { return language_->text(); }

bool MediaInputWidget::getFavourite() const { return favourite_->isChecked(); }

std::vector<QString> MediaInputWidget::getGenres() const {
  std::vector<QString> genres;
  for (auto *genre : genres_) {
    genres.push_back(genre->text());
  }
  return genres;
}
}  // namespace advanced_search
}  // namespace gui

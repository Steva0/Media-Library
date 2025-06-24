#include "MediaInputWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace gui {
namespace advanced_search {
const int MediaInputWidget::kColumnAmount = 6;

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
}

}  // namespace advanced_search
}  // namespace gui

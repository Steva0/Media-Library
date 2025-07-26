#include "MovieEditWidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

namespace gui {

MovieEditWidget::MovieEditWidget(QWidget* parent, bool note) : MediaEditWidget(parent) {
  auto* row_layout = new QHBoxLayout();

  // Durata
  auto* length_label = new QLabel("Durata (min):", this);
  length_input_ = new QSpinBox(this);
  length_input_->setRange(0, 1000);
  length_input_->setMaximumWidth(80);
  row_layout->addWidget(length_label);
  row_layout->addWidget(length_input_);

  row_layout->addSpacing(10);

  // Universo
  auto* universe_label = new QLabel("Universo:", this);
  universe_input_ = new QLineEdit(this);
  row_layout->addWidget(universe_label);
  row_layout->addWidget(universe_input_);

  row_layout->addStretch();

  main_layout_->addLayout(row_layout);

  auto* cast_row_layout = new QHBoxLayout();

  // Label Cast (sinistra, allineata in alto)
  auto* cast_label = new QLabel("Cast:", this);
  cast_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  cast_row_layout->addWidget(cast_label);

  // Layout verticale a destra per input + lista
  auto* cast_right_layout = new QVBoxLayout();

  // Input cast e bottone +
  auto* add_cast_layout = new QHBoxLayout();
  cast_input_ = new QLineEdit(this);
  add_cast_button_ = new QPushButton("+", this);
  add_cast_button_->setFixedWidth(30);
  add_cast_layout->addWidget(cast_input_);
  add_cast_layout->addWidget(add_cast_button_);
  cast_right_layout->addLayout(add_cast_layout);

  // Contenitore con layout verticale per lista cast (aggiunta dinamica)
  cast_container_ = new QWidget(this);
  cast_layout_ = new QVBoxLayout(cast_container_);
  cast_layout_->setContentsMargins(0, 0, 0, 0);
  cast_layout_->setSpacing(5);

  // Scrolling per la lista cast
  auto* cast_scroll = new QScrollArea(this);
  cast_scroll->setWidget(cast_container_);
  cast_scroll->setWidgetResizable(true);
  cast_scroll->setFixedHeight(100);

  cast_right_layout->addWidget(cast_scroll);

  cast_row_layout->addLayout(cast_right_layout);

  main_layout_->addLayout(cast_row_layout);

  if (note) {
    addNotesSection(main_layout_);
  }
  connect(add_cast_button_, &QPushButton::clicked, this, &MovieEditWidget::addCastMember);
}

void MovieEditWidget::setMedia(const media::Media* media) {
  MediaEditWidget::setMedia(media);
  const media::Movie* movie = dynamic_cast<const media::Movie*>(media);
  if (!movie) return;

  length_input_->setValue(movie->getLength());
  universe_input_->setText(QString::fromStdString(movie->getUniverse()));

  clearCast();
  setCast(movie->getCast());
}

void MovieEditWidget::clearCast() {
  for (auto& pair : cast_widgets_) {
    cast_layout_->removeWidget(pair.first);
    cast_layout_->removeWidget(pair.second);
    pair.first->deleteLater();
    pair.second->deleteLater();
  }
  cast_widgets_.clear();
}

void MovieEditWidget::setCast(const std::vector<std::string>& cast) {
  for (const auto& member : cast) {
    // Creazione widget per ogni membro cast
    auto* cast_line = new QLineEdit(QString::fromStdString(member), this);
    cast_line->setEnabled(false);

    auto* remove_button = new QPushButton("-", this);
    remove_button->setFixedWidth(30);

    // Layout orizzontale per riga cast
    auto* row_layout = new QHBoxLayout();
    row_layout->addWidget(cast_line);
    row_layout->addWidget(remove_button);

    cast_layout_->addLayout(row_layout);
    cast_widgets_.push_back(qMakePair(cast_line, remove_button));

    connect(remove_button, &QPushButton::clicked, this,
            [this, cast_line, remove_button]() { removeCastMember(cast_line, remove_button); });
  }
}

void MovieEditWidget::addCastMember() {
  QString text = cast_input_->text().trimmed();
  if (text.isEmpty()) return;

  // Controlla duplicati
  for (auto& pair : cast_widgets_) {
    if (pair.first->text() == text) {
      cast_input_->clear();
      return;
    }
  }

  // Crea nuovi widget riga
  auto* cast_line = new QLineEdit(text, this);
  cast_line->setEnabled(false);

  auto* remove_button = new QPushButton("-", this);
  remove_button->setFixedWidth(30);

  auto* row_layout = new QHBoxLayout();
  row_layout->addWidget(cast_line);
  row_layout->addWidget(remove_button);

  cast_layout_->addLayout(row_layout);
  cast_widgets_.push_back(qMakePair(cast_line, remove_button));

  connect(remove_button, &QPushButton::clicked, this,
          [this, cast_line, remove_button]() { removeCastMember(cast_line, remove_button); });

  cast_input_->clear();
}

void MovieEditWidget::removeCastMember(QLineEdit* cast_line, QPushButton* button) {
  auto it = std::find_if(cast_widgets_.begin(), cast_widgets_.end(),
                         [cast_line, button](const QPair<QLineEdit*, QPushButton*>& pair) {
                           return pair.first == cast_line && pair.second == button;
                         });
  if (it == cast_widgets_.end()) return;

  cast_layout_->removeWidget(it->first);
  cast_layout_->removeWidget(it->second);
  it->first->deleteLater();
  it->second->deleteLater();

  cast_widgets_.erase(it);
}

std::vector<std::string> MovieEditWidget::getCast() const {
  std::vector<std::string> result;
  for (const auto& pair : cast_widgets_) {
    result.push_back(pair.first->text().toStdString());
  }
  return result;
}

media::Media* MovieEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::Movie(title_input_->text().toStdString(), release_input_->value(),
                          language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                          img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(), getCast(),
                          length_input_->value(), universe_input_->text().toStdString());
}

void MovieEditWidget::clearInputFields() {
  MediaEditWidget::clearInputFields();
  length_input_->setValue(0);
  universe_input_->clear();
  clearCast();
}

}  // namespace gui

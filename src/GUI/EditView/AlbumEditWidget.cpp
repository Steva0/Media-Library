#include "AlbumEditWidget.h"

#include <QLabel>
#include <QScrollArea>

namespace gui {

AlbumEditWidget::AlbumEditWidget(QWidget* parent) : MediaEditWidget(parent) {
  // --- Band name (etichetta a sinistra, campo più compatto) ---
  auto* band_layout = new QHBoxLayout();
  auto* band_label = new QLabel("Band:", this);
  band_label->setFixedWidth(50);  // larghezza costante della label
  band_layout->addWidget(band_label);

  band_layout->addSpacing(5);

  band_input_ = new QLineEdit(this);
  band_input_->setMaximumWidth(300);  // restringe il campo input
  band_layout->addWidget(band_input_);
  band_layout->addStretch();  // spinge tutto a sinistra

  main_layout_->addLayout(band_layout);

  // --- Membri della band stile "Generi" ---
  auto* band_members_row_layout = new QHBoxLayout();

  auto* band_members_label = new QLabel("Membri:", this);
  band_members_label->setAlignment(Qt::AlignTop);
  band_members_row_layout->addWidget(band_members_label);

  auto* band_members_right_layout = new QVBoxLayout();

  band_member_input_ = new QLineEdit(this);
  add_band_member_button_ = new QPushButton("+", this);
  add_band_member_button_->setFixedWidth(30);
  connect(add_band_member_button_, &QPushButton::clicked, this, &AlbumEditWidget::addBandMember);

  auto* add_band_member_layout = new QHBoxLayout();
  add_band_member_layout->addWidget(band_member_input_);
  add_band_member_layout->addWidget(add_band_member_button_);
  band_members_right_layout->addLayout(add_band_member_layout);

  band_members_layout_ = new QGridLayout();
  band_members_layout_->setSpacing(5);
  band_members_layout_->setContentsMargins(0, 0, 0, 0);

  auto* band_members_container = new QWidget(this);
  band_members_container->setLayout(band_members_layout_);

  auto* band_members_scroll = new QScrollArea(this);
  band_members_scroll->setWidget(band_members_container);
  band_members_scroll->setWidgetResizable(true);
  band_members_scroll->setFixedHeight(100);
  band_members_right_layout->addWidget(band_members_scroll);

  band_members_row_layout->addLayout(band_members_right_layout);
  main_layout_->addLayout(band_members_row_layout);

  // --- Canzoni stile "Generi" ---
  auto* songs_row_layout = new QHBoxLayout();

  auto* songs_label = new QLabel("Canzoni:", this);
  songs_label->setAlignment(Qt::AlignTop);
  songs_row_layout->addWidget(songs_label);

  auto* songs_right_layout = new QVBoxLayout();

  song_input_ = new QLineEdit(this);
  add_song_button_ = new QPushButton("+", this);
  add_song_button_->setFixedWidth(30);
  connect(add_song_button_, &QPushButton::clicked, this, &AlbumEditWidget::addSong);

  auto* song_input_layout = new QHBoxLayout();
  song_input_layout->addWidget(song_input_);
  song_input_layout->addWidget(add_song_button_);
  songs_right_layout->addLayout(song_input_layout);

  songs_layout_ = new QGridLayout();
  songs_layout_->setSpacing(5);
  songs_layout_->setContentsMargins(0, 0, 0, 0);

  auto* songs_container = new QWidget(this);
  songs_container->setLayout(songs_layout_);

  auto* songs_scroll = new QScrollArea(this);
  songs_scroll->setWidget(songs_container);
  songs_scroll->setWidgetResizable(true);
  songs_scroll->setFixedHeight(100);
  songs_right_layout->addWidget(songs_scroll);

  songs_row_layout->addLayout(songs_right_layout);
  main_layout_->addLayout(songs_row_layout);

  addNotesSection(main_layout_);
}

void AlbumEditWidget::addBandMember() {
  QString text = band_member_input_->text().trimmed();
  if (text.isEmpty()) return;

  for (auto* edit : band_member_edits_) {
    if (edit->text() == text) {
      band_member_input_->clear();
      return;
    }
  }

  int row = band_members_layout_->rowCount();

  auto* new_member = new QLineEdit(text, this);
  new_member->setEnabled(false);
  band_members_layout_->addWidget(new_member, row, 0);
  band_member_edits_.push_back(new_member);

  auto* remove_button = new QPushButton("-", this);
  remove_button->setFixedWidth(30);
  band_members_layout_->addWidget(remove_button, row, 1);

  connect(remove_button, &QPushButton::clicked, this, [this, new_member, remove_button]() {
    removeBandMember(new_member);
    new_member->deleteLater();
    remove_button->deleteLater();
  });

  band_member_input_->clear();
}

void AlbumEditWidget::removeBandMember(QLineEdit* member_edit) {
  auto it = std::find(band_member_edits_.begin(), band_member_edits_.end(), member_edit);
  if (it != band_member_edits_.end()) {
    band_member_edits_.erase(it);
  }
}

void AlbumEditWidget::addSong() {
  QString text = song_input_->text().trimmed();
  if (text.isEmpty()) return;

  for (auto* edit : song_edits_) {
    if (edit->text() == text) {
      song_input_->clear();
      return;
    }
  }

  int row = songs_layout_->rowCount();

  auto* new_song = new QLineEdit(text, this);
  new_song->setEnabled(false);
  songs_layout_->addWidget(new_song, row, 0);
  song_edits_.push_back(new_song);

  auto* remove_button = new QPushButton("-", this);
  remove_button->setFixedWidth(30);
  songs_layout_->addWidget(remove_button, row, 1);

  connect(remove_button, &QPushButton::clicked, this, [this, new_song, remove_button]() {
    removeSong(new_song);
    new_song->deleteLater();
    remove_button->deleteLater();
  });

  song_input_->clear();
}

void AlbumEditWidget::removeSong(QLineEdit* song_edit) {
  auto it = std::find(song_edits_.begin(), song_edits_.end(), song_edit);
  if (it != song_edits_.end()) {
    song_edits_.erase(it);
  }
}

void AlbumEditWidget::setMedia(const media::Media* media) {
  MediaEditWidget::setMedia(media);

  const media::Album* album = dynamic_cast<const media::Album*>(media);
  if (!album) return;

  band_input_->setText(QString::fromStdString(album->getBand()));

  clearGridLayout(band_members_layout_, band_member_edits_);
  clearGridLayout(songs_layout_, song_edits_);

  // Pulisci canzoni attuali
  for (auto* edit : song_edits_) {
    edit->parentWidget()->deleteLater();
  }
  song_edits_.clear();

  for (const auto& song : album->getSongs()) {
    song_input_->setText(QString::fromStdString(song));
    addSong();
  }
}

media::Media* AlbumEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  std::vector<std::string> members;
  for (auto* edit : band_member_edits_) {
    members.push_back(edit->text().toStdString());
  }

  std::vector<std::string> songs;
  for (auto* edit : song_edits_) {
    songs.push_back(edit->text().toStdString());
  }

  return new media::Album(title_input_->text().toStdString(), release_input_->value(),
                          language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                          img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(),
                          band_input_->text().toStdString(), members, songs);
}

void AlbumEditWidget::clearInputFields() {
  MediaEditWidget::clearInputFields();
  band_input_->clear();

  clearGridLayout(band_members_layout_, band_member_edits_);
  clearGridLayout(songs_layout_, song_edits_);
}

void clearGridLayout(QGridLayout* layout, std::vector<QLineEdit*>& edits) {
  QLayoutItem* item;
  while ((item = layout->takeAt(0)) != nullptr) {
    if (QWidget* widget = item->widget()) {
      widget->deleteLater();
    }
    delete item;
  }
  edits.clear();
}


}  // namespace gui

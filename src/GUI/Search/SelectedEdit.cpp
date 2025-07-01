#include "SelectedEdit.h"

#include <QGridLayout>
#include <QIntValidator>
#include <QPushButton>
#include <limits>

namespace gui {
namespace search {
SelectedEdit::SelectedEdit(QWidget *parent)
    : QWidget(parent),
      type_(new QLabel(this)),
      preview_(new QLabel(this)),
      title_(new QLineEdit(this)),
      release_(new QLineEdit(this)),
      language_(new QLineEdit(this)),
      favourite_(new QCheckBox(this)) {
  auto *edit_layout = new QHBoxLayout;
  auto *right_layout = new QVBoxLayout;
  auto *data_layout = new QGridLayout;

  data_layout->addWidget(new QLabel("Title:", this), 0, 0);
  data_layout->addWidget(title_, 0, 1);

  data_layout->addWidget(new QLabel("Release:", this), 1, 0);
  data_layout->addWidget(release_, 1, 1);
  release_->setValidator(new QIntValidator(-5000, 5000, release_));

  data_layout->addWidget(new QLabel("Language:", this), 2, 0);
  data_layout->addWidget(language_, 2, 1);

  data_layout->addWidget(new QLabel("Favourite:", this), 3, 0);
  data_layout->addWidget(favourite_, 3, 1);

  right_layout->addWidget(type_);
  right_layout->addLayout(data_layout);
  right_layout->setAlignment(Qt::AlignTop);

  edit_layout->addWidget(preview_);
  edit_layout->addLayout(right_layout);
  edit_layout->setAlignment(Qt::AlignLeft);

  cancel_ = new QPushButton("Cancel", this);
  confirm_ = new QPushButton("Confirm", this);
  delete_ = new QPushButton("Delete", this);

  auto *layout = new QGridLayout(this);
  layout->addLayout(edit_layout, 0, 0, Qt::AlignTop | Qt::AlignLeft);
  layout->addWidget(delete_, 0, 1, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(cancel_, 1, 0, Qt::AlignBottom | Qt::AlignLeft);
  layout->addWidget(confirm_, 1, 1, Qt::AlignRight | Qt::AlignBottom);

  connect(title_, &QLineEdit::textChanged, [this]() { title_->setStyleSheet("background-color: white;"); });
  connect(cancel_, &QAbstractButton::clicked, [this]() { emit undoChanges(); });
  connect(confirm_, &QAbstractButton::clicked, this, &SelectedEdit::makeMediaAndCommit);
  connect(delete_, &QAbstractButton::clicked, [this]() { emit requestDelete(selected_); });
}

void SelectedEdit::display(const media::Media *media) {
  selected_ = media;
  if (media) {
    MediaTypeProbe probe;
    media->accept(probe);
    type_->setText(probe.type_);

    if (media->getImgPath() == "" || QPixmap(QString::fromStdString(media->getImgPath())).isNull())
      preview_->setPixmap(QPixmap(QString::fromStdString(":/assets/wifi.jpeg")));
    else {
      preview_->setPixmap(QPixmap(QString::fromStdString(media->getImgPath())).scaled(128, 128));
    }
    title_->setText(QString::fromStdString(media->getTitle()));
    release_->setText(QString::number(media->getRelease()));
    if (media->getRelease() == std::numeric_limits<int>::min()) release_->clear();
    language_->setText(QString::fromStdString(media->getLanguage()));
    favourite_->setChecked(media->isFavourite());
  }
}

void SelectedEdit::makeMediaAndCommit() {
  if (title_->text() == "") {
    title_->setStyleSheet("background-color: red");
    return;
  }
  MediaTypeClone v;
  selected_->accept(v);
  media::Media *new_media = v.clone_;
  new_media->setTitle(title_->text().toStdString());
  new_media->setRelease(release_->text().toInt());
  new_media->setLanguage(language_->text().toStdString());
  new_media->setFavourite(favourite_->isChecked());
  emit commitChanges(new_media, selected_);
}

void SelectedEdit::MediaTypeProbe::visit(const media::Media &) { type_ = "MEDIA"; }

void SelectedEdit::MediaTypeProbe::visit(const media::Album &) { type_ = "ALBUM"; }

void SelectedEdit::MediaTypeProbe::visit(const media::Movie &) { type_ = "MOVIE"; }

void SelectedEdit::MediaTypeProbe::visit(const media::Series &) { type_ = "SERIES"; }

void SelectedEdit::MediaTypeProbe::visit(const media::Novel &) { type_ = "NOVEL"; }

void SelectedEdit::MediaTypeProbe::visit(const media::AudioBook &) { type_ = "AUDIOBOOK"; }

void SelectedEdit::MediaTypeProbe::visit(const media::Ebook &) { type_ = "EBOOK"; }

void SelectedEdit::MediaTypeClone::visit(const media::Media &media) { clone_ = new media::Media(media); }

void SelectedEdit::MediaTypeClone::visit(const media::Album &album) { clone_ = new media::Album(album); }

void SelectedEdit::MediaTypeClone::visit(const media::Movie &movie) { clone_ = new media::Movie(movie); }

void SelectedEdit::MediaTypeClone::visit(const media::Series &series) { clone_ = new media::Series(series); }

void SelectedEdit::MediaTypeClone::visit(const media::Novel &novel) { clone_ = new media::Novel(novel); }

void SelectedEdit::MediaTypeClone::visit(const media::AudioBook &audiobook) {
  clone_ = new media::AudioBook(audiobook);
}

void SelectedEdit::MediaTypeClone::visit(const media::Ebook &ebook) { clone_ = new media::Ebook(ebook); }

}  // namespace search
}  // namespace gui

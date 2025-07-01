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

  title_edit_sheet_ = title_->styleSheet();
  connect(title_, &QLineEdit::textChanged, [this]() { title_->setStyleSheet(title_edit_sheet_); });
  connect(cancel_, &QAbstractButton::clicked, [this]() { emit undoChanges(); });
  connect(confirm_, &QAbstractButton::clicked, this, &SelectedEdit::makeMediaAndCommit);
  connect(delete_, &QAbstractButton::clicked, [this]() { emit requestDelete(selected_); });
}

void SelectedEdit::display(const media::Media *media) {
  selected_ = media;
  if (media) {
    type_->setText(QString::fromStdString(media->displayType()));

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
  if (title_->text().trimmed() == "") {
    title_->setStyleSheet("background-color: red");
    return;
  }
  media::Media *new_media = selected_->makePtr().release();
  new_media->setTitle(title_->text().toStdString());
  new_media->setRelease(release_->text().toInt());
  new_media->setLanguage(language_->text().toStdString());
  new_media->setFavourite(favourite_->isChecked());
  emit commitChanges(new_media, selected_);
}

}  // namespace search
}  // namespace gui

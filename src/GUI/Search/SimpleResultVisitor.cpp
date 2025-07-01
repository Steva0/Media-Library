#include "SimpleResultVisitor.h"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include "../../Media/Album.h"
#include "../../Media/AudioBook.h"
#include "../../Media/Ebook.h"
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Novel.h"
#include "../../Media/Series.h"

namespace gui {
namespace search {
QWidget *SimpleResultVisitor::getWidget() const { return result_; }
void SimpleResultVisitor::visit(const media::Media &media) {
  result_ = new QWidget;
  auto *layout = new QVBoxLayout(result_);

  auto *type = new QLabel(type_, result_);
  type->setAlignment(Qt::AlignCenter);

  auto *image = new QLabel(result_);
  if (media.getImgPath() == "" || QPixmap(QString::fromStdString(media.getImgPath())).isNull())
    image->setPixmap(QPixmap(QString::fromStdString(":/assets/matita.jpg")).scaled(128, 128, Qt::KeepAspectRatio));
  else {
    image->setPixmap(QPixmap(QString::fromStdString(media.getImgPath())).scaled(128, 128, Qt::KeepAspectRatio));
  }

  auto *title = new QLabel(QString::fromStdString(media.getTitle()), result_);
  title->setAlignment(Qt::AlignCenter);

  layout->addWidget(type);
  layout->addStretch();
  layout->addWidget(image);
  layout->addStretch();
  layout->addWidget(title);
}
void SimpleResultVisitor::visit(const media::Album &album) {
  type_ = "ALBUM";
  visit(static_cast<const media::Media &>(album));
}
void SimpleResultVisitor::visit(const media::Movie &movie) {
  type_ = "MOVIE";
  visit(static_cast<const media::Media &>(movie));
}
void SimpleResultVisitor::visit(const media::Series &series) {
  type_ = "SERIES";
  visit(static_cast<const media::Media &>(series));
}
void SimpleResultVisitor::visit(const media::Novel &novel) {
  type_ = "NOVEL";
  visit(static_cast<const media::Media &>(novel));
}
void SimpleResultVisitor::visit(const media::AudioBook &audiobook) {
  type_ = "AUDIOBOOK";
  visit(static_cast<const media::Media &>(audiobook));
}
void SimpleResultVisitor::visit(const media::Ebook &ebook) {
  type_ = "EBOOK";
  visit(static_cast<const media::Media &>(ebook));
}

}  // namespace search
}  // namespace gui

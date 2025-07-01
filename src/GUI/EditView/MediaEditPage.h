#ifndef GUI_MEDIAEDIT_MEDIAEDITPAGE_H
#define GUI_MEDIAEDIT_MEDIAEDITPAGE_H

#include <QKeyEvent>
#include <QStackedLayout>
#include <QWidget>
#include <memory>

#include "AlbumEditWidget.h"
#include "AudioBookEditWidget.h"
#include "EbookEditWidget.h"
#include "MediaEditWidget.h"
#include "MovieEditWidget.h"
#include "NovelEditWidget.h"
#include "SeriesEditWidget.h"

namespace media {
class Media;
}

namespace gui {

class MediaEditPage : public QWidget {
  Q_OBJECT
 public:
  explicit MediaEditPage(QWidget* parent = nullptr);

  void setMediaToEdit(const media::Media* media);
  void reset();

 signals:
  void editConfirmed(const media::Media* newMedia, const media::Media* oldMedia);
  void deleteRequested(const media::Media* media);
  void backRequested();

 private slots:
  void onConfirm();
  void onDelete();
  void onBack();

 protected:
  const media::Media* current_media_ = nullptr;

  // Contenitore widget di editing polimorfi
  QStackedLayout* stacked_layout_ = nullptr;

  // Punteri ai widget di editing per i vari tipi
  MediaEditWidget* media_edit_widget_ = nullptr;
  NovelEditWidget* novel_edit_widget_ = nullptr;
  AudioBookEditWidget* audiobook_edit_widget_ = nullptr;
  AlbumEditWidget* album_edit_widget_ = nullptr;
  SeriesEditWidget* series_edit_widget_ = nullptr;
  MovieEditWidget* movie_edit_widget_ = nullptr;
  EbookEditWidget* ebook_edit_widget_ = nullptr;

  void keyPressEvent(QKeyEvent* event) override;
  void setupUi();
  MediaEditWidget* getWidgetForMedia(const media::Media* media) const;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_MEDIAEDITPAGE_H

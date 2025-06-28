#ifndef GUI_MEDIADETAILS_MEDIADETAILPAGE_H
#define GUI_MEDIADETAILS_MEDIADETAILPAGE_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include "IMediaDetailWidget.h"
#include "MediaDetailWidget.h"
#include "NovelDetailWidget.h"
#include "MovieDetailWidget.h"
#include "AlbumDetailWidget.h"
#include "EbookDetailWidget.h"
#include "AudioBookDetailWidget.h"
#include "SeriesDetailWidget.h"
#include "../../Media/Media.h"

namespace gui {

class MediaDetailPage : public QWidget {
  Q_OBJECT
 public:
  explicit MediaDetailPage(QWidget* parent = nullptr);
  ~MediaDetailPage();

  void setMedia(const media::Media* media);

signals:
  void removeMediaRequested(const media::Media* media);
  void enterEditRequested(const media::Media* media);
  void backRequested();
  
private slots:
  void onRemoveClicked();
  void onEditClicked();

protected:
  void keyPressEvent(QKeyEvent* event) override;
  IMediaDetailWidget* currentDetailWidget_ = nullptr;
  const media::Media* currentMedia_ = nullptr;

  QVBoxLayout* mainLayout_;
  QPushButton* removeButton_;
  QPushButton* editButton_;

  void createDetailWidgetForMedia(const media::Media* media);
  void clearCurrentDetailWidget();
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_MEDIADETAILPAGE_H

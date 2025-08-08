#ifndef GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#include <QLineEdit>
#include <QStackedWidget>

#include "AlbumInputWidget.h"
#include "AudioBookInputWidget.h"
#include "EbookInputWidget.h"
#include "MediaInputWidget.h"
#include "MovieInputWidget.h"
#include "NovelInputWidget.h"
#include "SeriesInputWidget.h"
#include "TypeSelector.h"

namespace gui {
namespace advanced_search {
class InputWidget : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout *layout_;
  TypeSelector *type_selection_;

  IMediaInputWidget *media_filter_;
  std::unique_ptr<media::Media> current_filter_;

 public:
  explicit InputWidget(QWidget *parent = nullptr);

  const media::Media &getFilter();
  void makeFilterFrom(const MediaInputWidget &);
  void makeFilterFrom(const AlbumInputWidget &);
  void makeFilterFrom(const NovelInputWidget &);
  void makeFilterFrom(const AudioBookInputWidget &);
  void makeFilterFrom(const EbookInputWidget &);
  void makeFilterFrom(const MovieInputWidget &);
  void makeFilterFrom(const SeriesInputWidget &);

 private slots:
  void showTypeInput(int);

 signals:
  void performSearch(const media::Media &filter);
};
}  // namespace advanced_search
}  // namespace gui

#endif

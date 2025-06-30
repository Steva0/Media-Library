#ifndef GUI_I_SEARCH_WIDGET_H
#define GUI_I_SEARCH_WIDGET_H
#include <QWidget>

#include "../Media/Media.h"
namespace gui {
class AbstractSearchWidget : public QWidget {
  Q_OBJECT
public:
 explicit AbstractSearchWidget(QWidget *parent = nullptr) : QWidget(parent) {}
signals:
 void requestResults(const media::Media &);
 void updateResults(const std::vector<const media::Media *> &results);
};
}  // namespace gui

#endif

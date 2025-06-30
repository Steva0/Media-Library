#ifndef GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#include <QGridLayout>
#include <QLineEdit>

#include "../../Media/Novel.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
class NovelInputWidget : public MediaInputWidget {
  Q_OBJECT
 private:
  QLineEdit *author_;
  QLineEdit *publisher_;
  QLineEdit *series_;
  QLineEdit *isbn_;

 protected:
  QGridLayout *novel_layout_;

 public:
  explicit NovelInputWidget(QWidget *parent = nullptr);

  void setFromMedia(const media::Media &) override;
  void makeFilterFor(InputWidget &) const override;

  std::string getAuthor() const;
  std::string getPublisher() const;
  std::string getSeries() const;
  std::string getISBN() const;
};
}  // namespace advanced_search
}  // namespace gui
#endif

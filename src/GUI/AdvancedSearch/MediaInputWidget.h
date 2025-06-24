#ifndef GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#define GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpinBox>

namespace gui {
namespace advanced_search {
class MediaInputWidget : public QWidget {
  Q_OBJECT
 private:
  QGridLayout *layout_;
  QLineEdit *title_;
  QLineEdit *release_;
  QLineEdit *language_;
  QCheckBox *favourite_;
  QLineEdit *genre_input_;
  std::vector<QLineEdit *> genres_;

  static const int kColumnAmount;

 public:
  explicit MediaInputWidget(QWidget *parent);

 signals:
  void setTitle(QString);
  void setRelease(QString);
  void setLanguage(QString);
  void addGenre(QString);
  void removeGenre(QString);
};
}  // namespace advanced_search
}  // namespace gui

#endif

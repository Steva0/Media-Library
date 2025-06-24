#ifndef GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#define GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

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

  QString getTitle() const;
  int getRelease() const;
  QString getLanguage() const;
  bool getFavourite() const;
  std::vector<QString> getGenres() const;

  private slots:
   void addGenre();
   void removeGenre(QLineEdit *genre, QPushButton *button);
};
}  // namespace advanced_search
}  // namespace gui

#endif

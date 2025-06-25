#ifndef GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#define GUI_ADVANCED_SEARCH_MEDIA_WIDGET
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

namespace gui {
namespace advanced_search {
class MediaInputWidget : public QWidget {
  Q_OBJECT
  protected:
  void addWidget(QWidget *, QWidget *, bool half = false);
 private:
  QGridLayout *layout_;
  QLineEdit *title_;
  QLineEdit *release_;
  QLineEdit *language_;
  QCheckBox *favourite_;
  QLineEdit *genre_input_;
  std::vector<QLineEdit *> genres_;

  static const int kColumnAmount;
  static const size_t kMaxGenres;

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

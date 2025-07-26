#ifndef GUI_TYPE_SELECTOR_H
#define GUI_TYPE_SELECTOR_H
#include <QButtonGroup>
#include <QPushButton>
#include <QWidget>

#include "../../Memory/Database.h"

namespace gui {
namespace advanced_search {
class TypeSelector : public QWidget {
  Q_OBJECT

 private:
  QButtonGroup *container_;
  std::array<QPushButton *, static_cast<size_t>(memory::Database::Type::TypeFilterCount)> types_;

 public:
  explicit TypeSelector(QWidget *parent = nullptr);

 signals:
  void selectType(int);
};
}  // namespace advanced_search
}  // namespace gui
#endif

#ifndef GUI_SEARCH_SIMPLE_RESULT_VISITOR_H
#define GUI_SEARCH_SIMPLE_RESULT_VISITOR_H
#include "../../Media/IConstMediaVisitor.h"
#include <QWidget>

namespace gui {
namespace search {
class SimpleResultVisitor : public media::IConstMediaVisitor {
 private:
  QWidget *result_;
  QString type_;

  void visit(const media::Media &) override;
 public:
  QWidget *getResult() const;

  void visit(const media::Album &) override;
  void visit(const media::Movie &) override;
  void visit(const media::Series &) override;
  void visit(const media::Novel &) override;
  void visit(const media::AudioBook &) override;
  void visit(const media::Ebook &) override;
};
}  // namespace search
}  // namespace gui
#endif

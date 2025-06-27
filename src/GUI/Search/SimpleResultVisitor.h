#ifndef GUI_SEARCH_SIMPLE_RESULT_VISITOR_H
#define GUI_SEARCH_SIMPLE_RESULT_VISITOR_H
#include <QWidget>

#include "../IMediaWidgetVisitor.h"

namespace gui {
namespace search {
class SimpleResultVisitor : public IMediaWidgetVisitor {
 private:
  QWidget *result_;
  QString type_;

  void visit(const media::Media &) override;

 public:
  QWidget *getWidget() const override;

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

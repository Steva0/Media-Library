#ifndef GUI_PREVIEW_VISITOR_H
#define GUI_PREVIEW_VISITOR_H
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFrame>

#include "../Media/IConstMediaVisitor.h"

namespace gui {
class PreviewVisitor : public media::IConstMediaVisitor {
 private:
  QString type_;
  // QFrame *result_;
  QWidget *result_;
  QGridLayout *data_;

  void addRowVector(const std::string &key, const std::vector<std::string> &values);
  void addRow(const std::string &key, const std::string &value);
  void addRow(const std::string &key, int value);
 public:
   QWidget *getResult() const;
  
  void visit(const media::Media &) override;
  void visit(const media::Album &) override;
  void visit(const media::Movie &) override;
  void visit(const media::Series &) override;
  void visit(const media::Novel &) override;
  void visit(const media::AudioBook &) override;
  void visit(const media::Ebook &) override;
};
}  // namespace gui

#endif

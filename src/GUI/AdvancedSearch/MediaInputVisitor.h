#ifndef GUI_ADVANCED_SEARCH_MEDIA_INPUT_VISITOR_H
#define GUI_ADVANCED_SEARCH_MEDIA_INPUT_VISITOR_H
#include "../IMediaWidgetVisitor.h"
#include "SubtypeInputWidget.h"
#include <QGridLayout>

namespace gui {
namespace advanced_search {
class MediaInputVisitor : public IMediaWidgetVisitor {
 private:
  SubtypeInputWidget *widget_;
  QGridLayout *layout_;
  
static const int kColumnAmount;
static const size_t kMaxGenre;
 public:
  SubtypeInputWidget *getWidget() override;
  void visit(const media::Media &) override;
  void visit(const media::Album &) override;
  void visit(const media::Movie &) override;
  void visit(const media::Series &) override;
  void visit(const media::Novel &) override;
  void visit(const media::AudioBook &) override;
  void visit(const media::Ebook &) override;
};
}  // namespace advanced_search
}  // namespace gui
#endif

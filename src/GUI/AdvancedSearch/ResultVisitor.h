#ifndef GUI_ADVANCED_SEARCH_RESULT_VISITOR_H
#define GUI_ADVANCED_SEARCH_RESULT_VISITOR_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "../../Media/IConstMediaVisitor.h"
#include "qgridlayout.h"
namespace gui {
namespace advanced_search {
class ResultVisitor : public media::IConstMediaVisitor {
 private:
  QGridLayout *grid_;
  // result_ sarà una composizione di immagine a sinistra e dati a destra
  QWidget *data_;
  QLabel *img_;
  // le voglio sempre in fondo quindi faccio un widget a parte
  // potrebbe valer la pena fare un widget a parte per gestire meglio l'ordine di visualizzazione
  // qualcosa come un `header_` e un `footer_`
  QLabel *notes_;

  void addRow(const std::string &, const std::string &);
  void addRow(const std::string &, int);
  void addRow(const std::string &, const std::vector<std::string> &);
  void addRow(const std::string &);

 public:
  QWidget *getResult();

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

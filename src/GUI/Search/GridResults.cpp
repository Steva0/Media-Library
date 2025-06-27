#include "GridResults.h"
#include <iostream>

namespace gui {
  namespace search {
    GridResults::GridResults(QWidget *parent) : QFrame(parent), grid_(new QGridLayout(this)) {
      
    }
    void GridResults::updateResults(const std::vector<const media::Media *> &results) {
      std::cout << "Ricevuti: " << results.size() << '\n';
    }
  }
}

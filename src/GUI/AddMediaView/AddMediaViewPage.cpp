#include "AddMediaViewPage.h".

#include <iostream>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>

namespace gui {

AddMediaViewPage::AddMediaViewPage(QWidget* parent) : QWidget(parent) {
  setupUi();
}

void AddMediaViewPage::setupUi() {
  auto* main_layout = new QVBoxLayout(this);

  // Top bar
  auto* top_bar_layout = new QHBoxLayout();
  auto* back_button = new QPushButton("← Back", this);
  back_button->setFixedSize(80, 30);
  connect(back_button, &QPushButton::clicked, this, &AddMediaViewPage::onBack);
  top_bar_layout->addWidget(back_button);
  top_bar_layout->addStretch();
  main_layout->addLayout(top_bar_layout);

  // Media type selector
  auto* type_selector_layout = new QHBoxLayout();
  const QStringList labels = {
    "Romanzo", "EBook", "Audiobook", "Film", "Serie", "Album"
  };

  for (int i = 0; i < labels.size(); ++i) {
    auto* button = new QPushButton(labels[i], this);
    connect(button, &QPushButton::clicked, this, [this, i]() { selectMediaType(i); });
    type_selector_layout->addWidget(button);
  }

  main_layout->addLayout(type_selector_layout);

  // Stacked layout for editing widgets
  stacked_layout_ = new QStackedLayout();
  novel_edit_widget_ = new NovelEditWidget(this);
  ebook_edit_widget_ = new EbookEditWidget(this);
  audiobook_edit_widget_ = new AudioBookEditWidget(this);
  movie_edit_widget_ = new MovieEditWidget(this);
  series_edit_widget_ = new SeriesEditWidget(this);
  album_edit_widget_ = new AlbumEditWidget(this);

  stacked_layout_->addWidget(novel_edit_widget_);   
  stacked_layout_->addWidget(ebook_edit_widget_);  
  stacked_layout_->addWidget(audiobook_edit_widget_); 
  stacked_layout_->addWidget(movie_edit_widget_);   
  stacked_layout_->addWidget(series_edit_widget_);  
  stacked_layout_->addWidget(album_edit_widget_);   

  stacked_layout_->setCurrentIndex(0);  // Default 

  main_layout->addLayout(stacked_layout_);

  // Bottom bar
  auto* bottom_layout = new QHBoxLayout();
  auto* confirm_button = new QPushButton("Aggiungi", this);
  connect(confirm_button, &QPushButton::clicked, this, &AddMediaViewPage::onConfirm);
  bottom_layout->addStretch();
  bottom_layout->addWidget(confirm_button);

  main_layout->addLayout(bottom_layout);
}

void AddMediaViewPage::selectMediaType(int index) {
  stacked_layout_->setCurrentIndex(index);
}

void AddMediaViewPage::onConfirm() {
  auto* current_widget = getWidgetAtIndex(stacked_layout_->currentIndex());
  if (!current_widget) return;

  media::Media* media = current_widget->getModifiedMedia(false);
  if (media) {emit mediaAdded(media);}
  else std::cout << "Nessun media aggiunto.\n";
  ;
}

MediaEditWidget* AddMediaViewPage::getWidgetAtIndex(int index) const {
  switch (index) {
    case 0: return novel_edit_widget_;
    case 1: return ebook_edit_widget_;
    case 2: return audiobook_edit_widget_;
    case 3: return movie_edit_widget_;
    case 4: return series_edit_widget_;
    case 5: return album_edit_widget_;
    default: return nullptr;
  }
}

void AddMediaViewPage::onBack() {
  emit backRequested();
}

void AddMediaViewPage::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    onBack();
    event->accept();
  } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    onConfirm();
    event->accept();
  } else {
    QWidget::keyPressEvent(event);
  }
}

}  // namespace gui

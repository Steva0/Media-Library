#include "MediaEditWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QScrollArea>
#include <QResizeEvent>
#include <algorithm>

namespace gui {

MediaEditWidget::MediaEditWidget(QWidget *parent) : IMediaEditWidget(parent) {
    // Layout principale orizzontale
    auto* split_layout = new QHBoxLayout(this);

    // Widget principale con layout verticale (form)
    auto* main_form_widget = new QWidget(this);
    main_layout_ = new QVBoxLayout(main_form_widget);
    main_layout_->setAlignment(Qt::AlignTop);
    main_form_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);


    // Aggiungo form a sinistra (2/3)
    split_layout->addWidget(main_form_widget, 2, Qt::AlignTop);

    // Label copertina a destra (1/3)
    cover_label_ = new QLabel(this);
    cover_label_->setAlignment(Qt::AlignCenter);
    split_layout->addWidget(cover_label_, 1);

    // --- Campi del form ---

    // Titolo
    auto* title_layout = new QHBoxLayout();
    auto* title_label = new QLabel(tr("Titolo:"), this);
    title_label->setFixedWidth(50);          
    title_input_ = new QLineEdit(this);
    title_input_->setFixedWidth(250);    
    title_layout->addWidget(title_label);
    title_layout->addWidget(title_input_);
    title_layout->addStretch();            
    main_layout_->addLayout(title_layout);


    // Riga con Anno di uscita, Lingua e Preferito
    auto* row_layout = new QHBoxLayout();

    // Anno di uscita
    auto* release_label = new QLabel(tr("Anno di uscita:"), this);
    release_input_ = new QSpinBox(this);
    release_input_->setRange(0, 4000);
    row_layout->addWidget(release_label);
    row_layout->addWidget(release_input_);

    // Lingua
    auto* language_label = new QLabel(tr("Lingua:"), this);
    language_input_ = new QLineEdit(this);
    language_input_->setFixedWidth(150);
    row_layout->addSpacing(10);  // Spazio tra i campi
    row_layout->addWidget(language_label);
    row_layout->addWidget(language_input_);

    // Preferito
    auto* favourite_label = new QLabel(tr("Preferito:"), this);
    favourite_checkbox_ = new QCheckBox(this);
    row_layout->addSpacing(10);  // Spazio tra i campi
    row_layout->addWidget(favourite_label);
    row_layout->addWidget(favourite_checkbox_);
    row_layout->addStretch();

    main_layout_->addLayout(row_layout);


    // Percorso immagine (label + pulsante + path sotto)
    img_select_button_ = new QPushButton(tr("Seleziona immagine..."), this);
    img_path_input_ = new QLabel(tr("(nessuna immagine selezionata)"), this);
    img_path_input_->setStyleSheet("font-style: italic; color: gray;");

    auto* img_layout = new QHBoxLayout();
    auto* img_label = new QLabel(tr("Percorso immagine:"), this);
    img_layout->addWidget(img_label);
    img_layout->addWidget(img_path_input_);
    img_layout->addStretch();
    main_layout_->addLayout(img_layout);
    main_layout_->addWidget(img_select_button_);

    connect(img_select_button_, &QPushButton::clicked, this, &MediaEditWidget::selectImageFile);

    // Layout orizzontale per l'intera sezione "Generi"
    auto* genres_row_layout = new QHBoxLayout();

    // Label "Generi" (in alto a sinistra)
    auto* genres_label = new QLabel(tr("Generi:"), this);
    genres_label->setAlignment(Qt::AlignTop);
    genres_row_layout->addWidget(genres_label);

    // Layout verticale per input + lista a destra
    auto* genres_right_layout = new QVBoxLayout();

    // Campo input e bottone "+"
    genre_input_ = new QLineEdit(this);
    add_genre_button_ = new QPushButton(tr("+"), this);
    add_genre_button_->setFixedWidth(30);

    auto* add_genre_layout = new QHBoxLayout();
    add_genre_layout->addWidget(genre_input_);
    add_genre_layout->addWidget(add_genre_button_);
    genres_right_layout->addLayout(add_genre_layout);

    // Lista dei generi (scrollable)
    genres_layout_ = new QGridLayout();
    genres_layout_->setSpacing(5);
    genres_layout_->setContentsMargins(0, 0, 0, 0);

    auto* genres_container = new QWidget(this);
    genres_container->setLayout(genres_layout_);

    auto* genres_scroll = new QScrollArea(this);
    genres_scroll->setWidget(genres_container);
    genres_scroll->setWidgetResizable(true);
    genres_scroll->setFixedHeight(100);

    genres_right_layout->addWidget(genres_scroll);

    // Aggiungo il layout destro a fianco della label
    genres_row_layout->addLayout(genres_right_layout);

    // Aggiungo il layout dei generi al layout principale
    main_layout_->addLayout(genres_row_layout);

    connect(add_genre_button_, &QPushButton::clicked, this, &MediaEditWidget::addGenre);

    // Note
    auto* notes_label = new QLabel(tr("Note:"), this);
    notes_input_ = new QTextEdit(this);
    const int line_height = QFontMetrics(notes_input_->font()).lineSpacing();
    notes_input_->setFixedHeight(line_height * 6 + 12);
    main_layout_->addWidget(notes_label);
    main_layout_->addWidget(notes_input_);

    old_media_ = nullptr;
    img_path_.clear();
}

void MediaEditWidget::selectImageFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Seleziona immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!fileName.isEmpty()) {
        img_path_ = fileName;
        img_path_input_->setText(img_path_);
        cover_pixmap_ = QPixmap(img_path_);
        updateCoverPixmap();
    }
}

void MediaEditWidget::updateCoverPixmap() {
    if (cover_pixmap_.isNull()) {
        cover_label_->clear();
        return;
    }

    int targetWidth = width() / 3;
    int targetHeight = cover_pixmap_.height() * targetWidth / cover_pixmap_.width();

    cover_label_->setPixmap(cover_pixmap_.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MediaEditWidget::resizeEvent(QResizeEvent* event) {
    IMediaEditWidget::resizeEvent(event);
    updateCoverPixmap();
}

void MediaEditWidget::setMedia(const media::Media* media) {
    if (!media) return;

    old_media_ = media;

    title_input_->setText(QString::fromStdString(media->getTitle()));
    release_input_->setValue(media->getRelease());
    language_input_->setText(QString::fromStdString(media->getLanguage()));
    favourite_checkbox_->setChecked(media->isFavourite());

    img_path_ = QString::fromStdString(media->getImgPath());
    if (img_path_.isEmpty() || img_path_ == "(nessuna immagine selezionata)") {
      img_path_input_->setText("(nessuna immagine selezionata)");
      img_path_input_->setStyleSheet("font-style: italic; color: gray;");
      cover_pixmap_ = QPixmap(":/assets/matita.jpg");  // immagine di default
    } else {
      img_path_input_->setText(img_path_);
      img_path_input_->setStyleSheet("");
      cover_pixmap_ = QPixmap(img_path_);
    }


    updateCoverPixmap();

    notes_input_->setText(QString::fromStdString(media->getNotes()));

    clearGenres();
    setGenres(media->getGenres());
}

void MediaEditWidget::clearGenres() {
    for (auto* genre_line : genres_) {
        genres_layout_->removeWidget(genre_line);
        genre_line->deleteLater();
    }
    genres_.clear();
}

void MediaEditWidget::setGenres(const std::vector<std::string>& genres) {
    int row = 0;
    for (const auto& genre : genres) {
        auto* genre_line = new QLineEdit(QString::fromStdString(genre), this);
        genre_line->setEnabled(false);
        genres_layout_->addWidget(genre_line, row, 0);
        genres_.push_back(genre_line);

        auto* remove_button = new QPushButton("-", this);
        remove_button->setFixedWidth(30);
        genres_layout_->addWidget(remove_button, row, 1);

        connect(remove_button, &QPushButton::clicked, this,
            [this, genre_line, remove_button]() { removeGenre(genre_line, remove_button); });

        row++;
    }
}

void MediaEditWidget::addGenre() {
    QString text = genre_input_->text().trimmed();
    if (text.isEmpty()) return;

    auto it = std::find_if(genres_.begin(), genres_.end(),
        [&](QLineEdit* le) { return le->text() == text; });
    if (it != genres_.end()) {
        genre_input_->clear();
        return;
    }

    int row = genres_layout_->rowCount();

    auto* new_genre = new QLineEdit(text, this);
    new_genre->setEnabled(false);
    genres_layout_->addWidget(new_genre, row, 0);
    genres_.push_back(new_genre);

    auto* remove_button = new QPushButton("-", this);
    remove_button->setFixedWidth(30);
    genres_layout_->addWidget(remove_button, row, 1);

    connect(remove_button, &QPushButton::clicked, this,
        [this, new_genre, remove_button]() { removeGenre(new_genre, remove_button); });

    genre_input_->clear();
}

void MediaEditWidget::removeGenre(QLineEdit* genre, QPushButton* button) {
    auto it = std::find(genres_.begin(), genres_.end(), genre);
    if (it == genres_.end()) return;

    genres_layout_->removeWidget(genre);
    genre->deleteLater();
    genres_.erase(it);

    genres_layout_->removeWidget(button);
    button->deleteLater();
}

std::vector<std::string> MediaEditWidget::getGenres() const {
    std::vector<std::string> result;
    for (auto* genre_line : genres_) {
        result.push_back(genre_line->text().toStdString());
    }
    return result;
}

media::Media* MediaEditWidget::getModifiedMedia() const {
    if (!old_media_) return nullptr;

    return new media::Media(
        title_input_->text().toStdString(),
        release_input_->value(),
        language_input_->text().toStdString(),
        favourite_checkbox_->isChecked(),
        getGenres(),
        img_path_.toStdString(),
        notes_input_->toPlainText().toStdString()
    );
}

}  // namespace gui

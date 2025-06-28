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

gui::MediaEditWidget::MediaEditWidget(QWidget *parent) : IMediaEditWidget(parent) {
    // Layout principale orizzontale
    auto* split_layout = new QHBoxLayout(this);

    // Widget principale con layout verticale (form)
    auto* main_form_widget = new QWidget(this);
    main_layout_ = new QVBoxLayout(main_form_widget);

    // Aggiungo form a sinistra (2/3)
    split_layout->addWidget(main_form_widget, 2);

    // Label copertina a destra (1/3)
    cover_label_ = new QLabel(this);
    cover_label_->setAlignment(Qt::AlignCenter);
    split_layout->addWidget(cover_label_, 1);

    // --- Campi del form ---

    // Titolo
    auto* title_layout = new QHBoxLayout();
    auto* title_label = new QLabel(tr("Titolo:"), this);
    title_input_ = new QLineEdit(this);
    title_layout->addWidget(title_label);
    title_layout->addWidget(title_input_);
    main_layout_->addLayout(title_layout);

    // Anno di uscita
    auto* release_layout = new QHBoxLayout();
    auto* release_label = new QLabel(tr("Anno di uscita:"), this);
    release_input_ = new QSpinBox(this);
    release_input_->setRange(1800, 2100);
    release_layout->addWidget(release_label);
    release_layout->addWidget(release_input_);
    main_layout_->addLayout(release_layout);

    // Lingua
    auto* language_layout = new QHBoxLayout();
    auto* language_label = new QLabel(tr("Lingua:"), this);
    language_input_ = new QLineEdit(this);
    language_layout->addWidget(language_label);
    language_layout->addWidget(language_input_);
    main_layout_->addLayout(language_layout);

    // Preferito
    auto* favourite_layout = new QHBoxLayout();
    auto* favourite_label = new QLabel(tr("Preferito:"), this);
    favourite_checkbox_ = new QCheckBox(this);
    favourite_layout->addWidget(favourite_label);
    favourite_layout->addWidget(favourite_checkbox_);
    favourite_layout->addStretch();
    main_layout_->addLayout(favourite_layout);

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

    // Note
    auto* notes_label = new QLabel(tr("Note:"), this);
    notes_input_ = new QTextEdit(this);
    const int line_height = QFontMetrics(notes_input_->font()).lineSpacing();
    notes_input_->setFixedHeight(line_height * 3 + 12);
    main_layout_->addWidget(notes_label);
    main_layout_->addWidget(notes_input_);

    // Generi
    auto* genres_label = new QLabel(tr("Generi:"), this);
    main_layout_->addWidget(genres_label);

    genre_input_ = new QLineEdit(this);
    add_genre_button_ = new QPushButton(tr("+"), this);
    add_genre_button_->setFixedWidth(30);

    auto* add_genre_layout = new QHBoxLayout();
    add_genre_layout->addWidget(genre_input_);
    add_genre_layout->addWidget(add_genre_button_);
    main_layout_->addLayout(add_genre_layout);

    genres_layout_ = new QGridLayout();
    genres_layout_->setSpacing(5);
    genres_layout_->setContentsMargins(0, 0, 0, 0);

    auto* genres_container = new QWidget(this);
    genres_container->setLayout(genres_layout_);

    auto* genres_scroll = new QScrollArea(this);
    genres_scroll->setWidget(genres_container);
    genres_scroll->setWidgetResizable(true);
    genres_scroll->setFixedHeight(100);
    main_layout_->addWidget(genres_scroll);

    connect(add_genre_button_, &QPushButton::clicked, this, &MediaEditWidget::addGenre);

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
    if (img_path_.isEmpty()) {
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

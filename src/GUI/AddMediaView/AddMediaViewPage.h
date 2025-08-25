#ifndef GUI_MEDIAEDIT_ADDMEDIAVIEWPAGE_H
#define GUI_MEDIAEDIT_ADDMEDIAVIEWPAGE_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QVector>

#include "../EditView/AlbumEditWidget.h"
#include "../EditView/AudioBookEditWidget.h"
#include "../EditView/EbookEditWidget.h"
#include "../EditView/MediaEditWidget.h"
#include "../EditView/MovieEditWidget.h"
#include "../EditView/NovelEditWidget.h"
#include "../EditView/SeriesEditWidget.h"

namespace gui {

class AddMediaViewPage : public QWidget {
    Q_OBJECT

public:
    explicit AddMediaViewPage(QWidget* parent = nullptr);
    void clearEditSection();

signals:
    void mediaAdded(media::Media* newMedia);
    void backRequested();

private slots:
    void onConfirm();
    void onBack();
    void selectMediaType(int index);

protected:
    void setupUi();
    void keyPressEvent(QKeyEvent* event) override;

private:
    QVector<QPushButton*> media_type_buttons_;
    QButtonGroup* media_type_group_ = nullptr;

    QStackedLayout* stacked_layout_ = nullptr;

    MediaEditWidget* media_edit_widget_ = nullptr;
    NovelEditWidget* novel_edit_widget_ = nullptr;
    AudioBookEditWidget* audiobook_edit_widget_ = nullptr;
    AlbumEditWidget* album_edit_widget_ = nullptr;
    SeriesEditWidget* series_edit_widget_ = nullptr;
    MovieEditWidget* movie_edit_widget_ = nullptr;
    EbookEditWidget* ebook_edit_widget_ = nullptr;

    MediaEditWidget* getWidgetAtIndex(int index) const;

    QWidget* edit_section_ = nullptr;
    QStackedLayout* central_layout_ = nullptr;

    QWidget* createButtonsWidget(QWidget* parent = nullptr);
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_ADDMEDIAVIEWPAGE_H

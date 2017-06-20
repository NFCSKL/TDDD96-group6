#include "bookmarkwidget.h"
#include "Library/customdialog.h"
BookmarkWidget::BookmarkWidget(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout();
    QPushButton* generate_btn = new QPushButton(tr("Generate"));
    init_bookmark_list();
    setLayout(layout);
    layout->addWidget(bookmark_list);
    layout->addWidget(generate_btn);
}

void BookmarkWidget::add_bookmark(BookmarkItem* bm_item) {
    bookmark_list->addItem(bm_item);
}

void BookmarkWidget::create_bookmark(VideoProject* vid_proj, const int frame_nbr, cv::Mat)
{
    qDebug() << "create bookmark";
    bool ok;
    if(!ok) return;
    QString text = get_input_text("", &ok);
    add_bookmark(new BookmarkItem(new Bookmark(vid_proj,text.toStdString(),frame_nbr), bookmark_list));
}

void BookmarkWidget::init_bookmark_list()
{
    QVBoxLayout* layout = new QVBoxLayout();
    bookmark_list = new QListWidget();
    bookmark_list->setLayout(layout);
}
/**
 * @brief BookmarkWidget::get_input_text
 * @param bookmark_text Text shown in the text edit when opening the dialog.
 * @param ok Parameter set to false if the user cancels.
 * @return Returns a description for the bookmark,
 *         obtained from the user.
 */
QString BookmarkWidget::get_input_text(std::string bookmark_text, bool* ok) {
    // Create the dialog
    CustomDialog dialog("Bookmark description", NULL);
    dialog.addLabel("Write a description of the bookmark:");
    dialog.addTextEdit(&bookmark_text, false, false, TEXT_EDIT_MIN_HEIGHT,
                          "Write a description of the bookmark. This will be used when creating a report.");

    // Show the dialog (execution will stop here until the dialog is finished)
    dialog.exec();

    if (dialog.wasCancelled()) {
        *ok = false;
        return "";
    }
    *ok = true;
    return QString::fromStdString(bookmark_text);
}

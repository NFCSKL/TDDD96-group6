#include "bookmarkview.h"
#include "Library/customdialog.h"
#include <iostream>

/**
 * @brief BookmarkView::BookmarkView
 * Constructor.
 * @param parent Parent item of the BookmarkView.
 */
BookmarkView::BookmarkView(QListWidget* parent) {
    view = parent;    
}

/**
 * @brief BookmarkView::get_num_bookmarks
 * @return Returns the number of bookmarks.
 */
int BookmarkView::get_num_bookmarks() {
    return view->count();
}

/**
 * @brief BookmarkView::add_bookmark
 * Adds a bookmark to the bookmark view.
 * @param bookmark Bookmark to add.
 */
int BookmarkView::add_bookmark(Bookmark* bookmark) {
    BookmarkItem* bookmark_item = new BookmarkItem(bookmark, view);
    view->addItem(bookmark_item);
    this->boomark_items.insert(id_bookmark);
    return this->id_bookmark++;
}

/**
 * @brief BookmarkView::remove_bookmark
 * @param id
 * @return void
 * Erases bookmarkitem from bookmarkview.
 */
void BookmarkView::remove_bookmark(ID id){
    BookmarkItem* bookmark_item = this->boomark_items.at(id);
    view->removeItemWidget(bookmark_item);
    this->boomark_items.erase(id);
}

/**
 * @brief BookmarkView::get_input_text
 * @param ok Parameter set to false if the user cancels.
 * @return Returns a description for the bookmark,
 *         obtained from the user.
 */
QString BookmarkView::get_input_text(bool* ok) {
    std::string bookmark_text = "";

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

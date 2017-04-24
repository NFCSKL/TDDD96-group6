#ifndef BOOKMARKVIEW_H
#define BOOKMARKVIEW_H

#include "bookmarkitem.h"
#include <QListWidget>

class BookmarkView {
public:
    BookmarkView(QListWidget* parent);    
    void add_bookmark(Bookmark *bookmark);
    int get_num_bookmarks();
    QString get_input_text(bool* ok);
private:


    const int TEXT_EDIT_MIN_HEIGHT = 32;

    QListWidget* view;
};

#endif // BOOKMARKVIEW_H

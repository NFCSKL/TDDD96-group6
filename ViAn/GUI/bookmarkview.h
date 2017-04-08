#ifndef BOOKMARKVIEW_H
#define BOOKMARKVIEW_H

#include "bookmark.h"
#include <QListWidget>

class BookmarkView {
public:
    BookmarkView(QListWidget* parent);
    void add_bookmark(int frame_nbr, std::string file_path);
    int get_num_bookmarks();
private:
    QString get_input_text(bool* ok);

    const int BOOKMARK_THUMBNAIL_HEIGHT = 64;
    const int TEXT_EDIT_MIN_HEIGHT = 32;

    QListWidget* view;
};

#endif // BOOKMARKVIEW_H

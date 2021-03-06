#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle();
    Rectangle(QColor col, QPoint pos);
    cv::Mat draw(cv::Mat &frame) override;
    void handle_new_pos(QPoint pos) override;
    void write(QJsonObject& json) override;
    void read(const QJsonObject& json) override;
};

#endif // RECTANGLE_H

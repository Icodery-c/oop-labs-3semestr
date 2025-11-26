#include "shapefactory.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"
#include <QDebug>
#include "group.h"


std::unique_ptr<BaseShape> TextShapeFactory::createShape(const QString& type)
{
    if (type == "Circle") {
        return std::make_unique<Circle>(QPoint(0, 0));
    } else if (type == "Rectangle") {
        return std::make_unique<Rectangle>(QPoint(0, 0));
    } else if (type == "Triangle") {
        return std::make_unique<Triangle>(QPoint(0, 0));
    } else if (type == "Line") {
        return std::make_unique<Line>(QPoint(0, 0));
    } else if (type == "Group") {
        return std::make_unique<Group>();
    }

    qDebug() << "Unknown shape type:" << type;
    return nullptr;
}



std::unique_ptr<BaseShape> TextShapeFactory::loadShape(QTextStream& stream)
{
    QString type;
    stream >> type;

    auto shape = createShape(type);
    if (shape) {
        shape->load(stream);
    }

    return shape;
}

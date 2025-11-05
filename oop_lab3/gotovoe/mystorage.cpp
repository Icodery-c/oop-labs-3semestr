#include "mystorage.h"

void MyStorage::add(const CCircle &circle)
{
    circles.push_back(circle);
}

void MyStorage::drawAll(QPainter &painter) const
{
    for (const auto &circle : circles)
        circle.draw(painter);
}

void MyStorage::deselectAll()
{
    for (auto &circle : circles)
        circle.setSelected(false);
}

CCircle* MyStorage::getCircleAt(int x, int y)
{
    for (auto &circle : circles)
        if (circle.contains(x, y))
            return &circle;
    return nullptr;
}

void MyStorage::removeSelected()
{
    circles.erase(
        std::remove_if(circles.begin(), circles.end(),
                       [](const CCircle &c) { return c.isSelected(); }),
        circles.end());
}

int MyStorage::size() const
{
    return static_cast<int>(circles.size());
}

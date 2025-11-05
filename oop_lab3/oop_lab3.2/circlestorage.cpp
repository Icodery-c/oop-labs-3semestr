#include "circlestorage.h"
#include <algorithm>

CircleStorage::CircleStorage()
{
}

CircleStorage::~CircleStorage()
{
    // Очищаем память
    for (auto circle : m_circles) {
        delete circle;
    }
    m_circles.clear();
}

void CircleStorage::addCircle(CCircle* circle)
{
    m_circles.push_back(circle);
}

void CircleStorage::removeCircle(int index)
{
    if (index >= 0 && index < static_cast<int>(m_circles.size())) {
        delete m_circles[index];
        m_circles.erase(m_circles.begin() + index);
    }
}

void CircleStorage::removeSelectedCircles()
{
    m_circles.erase(
        std::remove_if(m_circles.begin(), m_circles.end(),
            [](CCircle* circle) {
                if (circle->isSelected()) {
                    delete circle;
                    return true;
                }
                return false;
            }),
        m_circles.end()
    );
}

int CircleStorage::getCount() const
{
    return static_cast<int>(m_circles.size());
}

CCircle* CircleStorage::getCircle(int index)
{
    if (index >= 0 && index < static_cast<int>(m_circles.size())) {
        return m_circles[index];
    }
    return nullptr;
}

const CCircle* CircleStorage::getCircle(int index) const
{
    if (index >= 0 && index < static_cast<int>(m_circles.size())) {
        return m_circles[index];
    }
    return nullptr;
}

void CircleStorage::selectCircleAt(int x, int y, bool ctrlPressed)
{
    if (!ctrlPressed) {
        clearSelection();
    }
    
    // Выделяем все круги, содержащие точку (с конца для визуального порядка)
    for (int i = static_cast<int>(m_circles.size()) - 1; i >= 0; --i) {
        if (m_circles[i]->containsPoint(x, y)) {
            m_circles[i]->setSelected(!m_circles[i]->isSelected());
            break; // Выделяем только верхний круг
        }
    }
}

void CircleStorage::clearSelection()
{
    for (auto circle : m_circles) {
        circle->setSelected(false);
    }
}

#pragma once
#include "circle.h"
#include <vector>

class CircleStorage
{
private:
    std::vector<CCircle*> m_circles;

public:
    CircleStorage();
    ~CircleStorage();
    
    // Добавление и удаление
    void addCircle(CCircle* circle);
    void removeCircle(int index);
    void removeSelectedCircles();
    
    // Доступ к кругам
    int getCount() const;
    CCircle* getCircle(int index);
    const CCircle* getCircle(int index) const;
    
    // Работа с выделением
    void selectCircleAt(int x, int y, bool ctrlPressed = false);
    void clearSelection();
};


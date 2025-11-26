#pragma once

#include "ccircle.h"
#include <vector>

class MyStorage
{
private:
    std::vector<CCircle> circles;

public:
    void add(const CCircle &circle);
    void drawAll(QPainter &painter) const;
    void deselectAll();
    CCircle* getCircleAt(int x, int y);
    std::vector<CCircle*> getAllCirclesAt(int x, int y);
    void removeSelected();
    int size() const;
};

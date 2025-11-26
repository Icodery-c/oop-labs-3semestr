#pragma once

#include <QVector>

class CCircle;

class MyStorage {
public:
    MyStorage();
    ~MyStorage();

    void add(CCircle* c);
    int size() const;
    CCircle* at(int index) const;
    void removeAt(int index);

    // helpers
    void removeSelected();
    void clearSelection();

private:
    QVector<CCircle*> m_data;
};

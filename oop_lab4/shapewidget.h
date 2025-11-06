#pragma once

#include <QWidget>
#include "shapestorage.h"

class ShapeWidget : public QWidget
{
    Q_OBJECT

public:
    enum class Tool { Select, Circle, Rectangle, Triangle, Line };

private:
    ShapeStorage m_storage;
    Tool m_currentTool;  // Теперь Tool объявлен ДО использования

public:
    explicit ShapeWidget(QWidget *parent = nullptr);

    ShapeStorage& getStorage() { return m_storage; }

    // Методы для управления инструментами
    void setCurrentTool(Tool tool);
    void deleteSelectedShapes();
    void changeSelectedColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void createShapeAt(const QPoint& position);

signals:
    void selectionChanged();
    void shapesCountChanged(int count);
};

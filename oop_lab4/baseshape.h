#pragma once

#include <QPainter>
#include <QRect>
#include <QColor>

class BaseShape
{
protected:
    QPoint m_position;      // Позиция фигуры
    QColor m_color;         // Цвет заливки
    QColor m_borderColor;   // Цвет границы
    bool m_selected;        // Выделена ли фигура
    int m_borderWidth;      // Толщина границы

public:
    BaseShape(const QPoint& position, const QColor& color = Qt::blue);
    virtual ~BaseShape() = default;

    // Виртуальные методы (должны быть реализованы в наследниках)
    virtual void draw(QPainter& painter) const = 0;
    virtual bool contains(const QPoint& point) const = 0;
    virtual QRect getBoundingRect() const = 0;
    virtual QString getName() const = 0;

    // Общие методы (реализация в базовом классе)
    void move(int dx, int dy);
    void setPosition(const QPoint& newPosition);
    void setColor(const QColor& color);
    void setBorderColor(const QColor& color);
    void setSelected(bool selected);

    // Геттеры
    QPoint getPosition() const { return m_position; }
    QColor getColor() const { return m_color; }
    bool isSelected() const { return m_selected; }
    QString getColorName() const;

    // Проверка границ
    bool isWithinBounds(const QRect& bounds) const;

protected:
    // Вспомогательные методы для наследников
    void drawSelectionHighlight(QPainter& painter, const QRect& rect) const;
};

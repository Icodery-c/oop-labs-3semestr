#pragma once

#include <QPainter>
#include <QRect>
#include <QColor>
#include <QTextStream>

class BaseShape
{
protected:
    QPoint m_position;
    QColor m_color;
    QColor m_borderColor;
    bool m_selected;
    int m_borderWidth;

public:
    BaseShape(const QPoint& position, const QColor& color = Qt::blue);
    virtual ~BaseShape() = default;

    // Виртуальные методы
    virtual void draw(QPainter& painter) const = 0;
    virtual bool contains(const QPoint& point) const = 0;
    virtual QRect getBoundingRect() const = 0;
    virtual QRect getBoundsAfterResize(int dw, int dh) const = 0;
    virtual QString getName() const = 0;

    // Сериализация
    virtual void save(QTextStream& stream) const = 0;
    virtual void load(QTextStream& stream) = 0;
    virtual QString getType() const = 0;

    // Общие методы - ДЕЛАЕМ ВИРТУАЛЬНЫМИ
    virtual void move(int dx, int dy, const QRect& bounds);
    virtual bool canMove(int dx, int dy, const QRect& bounds) const;
    virtual bool canResize(int dw, int dh, const QRect& bounds) const;
    void setPosition(const QPoint& newPosition);
    virtual void setColor(const QColor& color);  // ← ДЕЛАЕМ ВИРТУАЛЬНЫМ
    void setBorderColor(const QColor& color);
    virtual void setSelected(bool selected);     // ← ДЕЛАЕМ ВИРТУАЛЬНЫМ

    // Геттеры
    QPoint getPosition() const { return m_position; }
    QColor getColor() const { return m_color; }
    bool isSelected() const { return m_selected; }
    QString getColorName() const;

    // Проверка границ
    bool isWithinBounds(const QRect& bounds) const;
    QRect getBoundsAfterMove(int dx, int dy) const;

protected:
    void drawSelectionHighlight(QPainter& painter, const QRect& rect) const;

    // Вспомогательные методы для сериализации
    void saveCommonProperties(QTextStream& stream) const;
    void loadCommonProperties(QTextStream& stream);
};

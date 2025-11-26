#pragma once

#include "baseshape.h"
#include <vector>
#include <memory>

class Group : public BaseShape
{
private:
    std::vector<std::unique_ptr<BaseShape>> m_children;
    QRect m_bounds;

public:
    Group();

    // Добавление/удаление фигур
    void addShape(std::unique_ptr<BaseShape> shape);
    void removeShape(BaseShape* shape);
    void clear();
    int getChildCount() const { return static_cast<int>(m_children.size()); }
    BaseShape* getChild(int index) {
        if (index >= 0 && index < static_cast<int>(m_children.size())) {
            return m_children[index].get();
        }
        return nullptr;
    }

    // Реализация виртуальных методов BaseShape
    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    QRect getBoundingRect() const override;
    QRect getBoundsAfterResize(int dw, int dh) const override;
    QString getName() const override { return "Group"; }

    // Сериализация
    void save(QTextStream& stream) const override;
    void load(QTextStream& stream) override;
    QString getType() const override { return "Group"; }

    // Переопределение операций для работы с группой
    void move(int dx, int dy, const QRect& bounds) override;
    void setColor(const QColor& color) override;      // ← ТЕПЕРЬ РАБОТАЕТ
    void setSelected(bool selected) override;         // ← ТЕПЕРЬ РАБОТАЕТ

private:
    void updateBounds();
};

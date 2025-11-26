#include "group.h"
#include <QDebug>
#include "shapefactory.h"

Group::Group()
    : BaseShape(QPoint(0, 0), Qt::gray)
{
    updateBounds();
}

void Group::addShape(std::unique_ptr<BaseShape> shape)
{
    m_children.push_back(std::move(shape));
    updateBounds();
    qDebug() << "Shape added to group. Total children:" << m_children.size();
}

void Group::removeShape(BaseShape* shape)
{
    auto it = std::remove_if(m_children.begin(), m_children.end(),
        [shape](const std::unique_ptr<BaseShape>& child) {
            return child.get() == shape;
        });

    m_children.erase(it, m_children.end());
    updateBounds();
    qDebug() << "Shape removed from group. Total children:" << m_children.size();
}

void Group::clear()
{
    m_children.clear();
    updateBounds();
}

void Group::draw(QPainter& painter) const
{
    painter.save();

    // Рисуем всех детей
    for (const auto& child : m_children) {
        child->draw(painter);
    }

    // Рисуем рамку группы если выделена
    if (m_selected) {
        drawSelectionHighlight(painter, m_bounds);

        // Подпись группы
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawText(m_bounds.topLeft() + QPoint(5, -5),
                        QString("Group (%1)").arg(m_children.size()));
    }

    painter.restore();
}

bool Group::contains(const QPoint& point) const
{
    // Проверяем попадание в любого из детей
    for (const auto& child : m_children) {
        if (child->contains(point)) {
            return true;
        }
    }
    return false;
}

QRect Group::getBoundingRect() const
{
    return m_bounds;
}

QRect Group::getBoundsAfterResize(int dw, int dh) const
{
    Q_UNUSED(dw);
    Q_UNUSED(dh);
    // Для группы изменение размера не поддерживается напрямую
    return m_bounds;
}

void Group::save(QTextStream& stream) const
{
    stream << getType() << " ";
    saveCommonProperties(stream);
    stream << m_children.size() << " ";

    // Сохраняем всех детей
    for (const auto& child : m_children) {
        child->save(stream);
    }

    stream << "\n";
}

void Group::load(QTextStream& stream)
{
    loadCommonProperties(stream);

    int childCount;
    stream >> childCount;

    m_children.clear();

    // Загружаем всех детей
    TextShapeFactory factory;
    for (int i = 0; i < childCount; ++i) {
        auto child = factory.loadShape(stream);
        if (child) {
            m_children.push_back(std::move(child));
        }
    }

    updateBounds();
    qDebug() << "Group loaded with" << m_children.size() << "children";
}

void Group::move(int dx, int dy, const QRect& bounds)
{
    // Проверяем можно ли переместить всю группу
    QRect newBounds = m_bounds.translated(dx, dy);
    if (bounds.contains(newBounds)) {
        // Перемещаем всех детей
        for (auto& child : m_children) {
            child->move(dx, dy, bounds);
        }
        m_position += QPoint(dx, dy);
        updateBounds();
        qDebug() << "Group moved by" << dx << dy;
    } else {
        qDebug() << "Group cannot move - out of bounds";
    }
}

void Group::setColor(const QColor& color)
{
    // Устанавливаем цвет всем детям
    for (auto& child : m_children) {
        child->setColor(color);
    }
    m_color = color;
}

void Group::setSelected(bool selected)
{
    // Устанавливаем выделение всем детям
    for (auto& child : m_children) {
        child->setSelected(selected);
    }
    m_selected = selected;
}

void Group::updateBounds()
{
    if (m_children.empty()) {
        m_bounds = QRect();
        m_position = QPoint(0, 0);
        return;
    }

    // Вычисляем общие границы всех детей
    m_bounds = m_children[0]->getBoundingRect();
    for (const auto& child : m_children) {
        m_bounds = m_bounds.united(child->getBoundingRect());
    }

    // Позиция группы - центр границ
    m_position = m_bounds.center();
}

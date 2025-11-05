#include "circlewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

CircleWidget::CircleWidget(QWidget *parent) 
    : QWidget(parent), m_ctrlPressed(false)
{
    setFocusPolicy(Qt::StrongFocus); // Для обработки клавиатуры
    setMinimumSize(400, 300);
}

CircleStorage& CircleWidget::getStorage()
{
    return m_storage;
}

void CircleWidget::deleteSelectedCircles()
{
    m_storage.removeSelectedCircles();
    update(); // Перерисовываем виджет
    emit circlesChanged();
}

void CircleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Заливаем фон
    painter.fillRect(rect(), Qt::white);
    
    // Рисуем все круги
    for (int i = 0; i < m_storage.getCount(); ++i) {
        m_storage.getCircle(i)->draw(painter);
    }
    
    // Отладочная информация
    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("Кругов: %1 | Ctrl: %2")
                    .arg(m_storage.getCount())
                    .arg(m_ctrlPressed ? "Да" : "Нет"));
}

void CircleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_ctrlPressed) {
            // Ctrl + клик - добавляем/убираем из выделения
            m_storage.selectCircleAt(event->pos().x(), event->pos().y(), true);
        } else {
            // Обычный клик - выделяем круг
            m_storage.selectCircleAt(event->pos().x(), event->pos().y(), false);
        }
        update();
        emit circlesChanged();
    } else if (event->button() == Qt::RightButton) {
        // Правый клик - создаем новый круг
        m_storage.addCircle(new CCircle(event->pos().x(), event->pos().y()));
        update();
        emit circlesChanged();
    }
}

void CircleWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        m_ctrlPressed = true;
    } else if (event->key() == Qt::Key_Delete) {
        deleteSelectedCircles();
    }
    update();
}

void CircleWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        m_ctrlPressed = false;
        update();
    }
}

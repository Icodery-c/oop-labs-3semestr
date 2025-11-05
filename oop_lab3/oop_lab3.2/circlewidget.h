#pragma once
#include <QWidget>
#include "circlestorage.h"

class CircleWidget : public QWidget
{
    Q_OBJECT

private:
    CircleStorage m_storage;
    bool m_ctrlPressed;

public:
    explicit CircleWidget(QWidget *parent = nullptr);
    
    // Методы для работы с хранилищем
    CircleStorage& getStorage();
    void deleteSelectedCircles();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void circlesChanged();
};


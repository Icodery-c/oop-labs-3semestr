#pragma once

#include <QMainWindow>
#include "numbermodel.h"
#include "numberview.h"

class MVCMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    NumberModel *m_model;
    NumberView *m_view;

public:
    MVCMainWindow(QWidget *parent = nullptr);
    ~MVCMainWindow();
};

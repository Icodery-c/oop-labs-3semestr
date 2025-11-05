#pragma once

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include "numbermodel.h"

class SingleNumberView : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *m_textEdit;
    QSpinBox *m_spinBox;
    QSlider *m_slider;
    QLabel *m_label;

    NumberModel *m_model;
    char m_valueType;
    bool m_isUpdating;

public:
    SingleNumberView(char valueType, const QString &label, NumberModel *model, QWidget *parent = nullptr);

private slots:
    void onModelChanged();
    void onTextEditChanged();
    void onSpinBoxChanged(int value);
    void onSliderChanged(int value);

private:
    void applyValueToModel(int value);
};

class NumberView : public QWidget
{
    Q_OBJECT

private:
    NumberModel *m_model;
    SingleNumberView *m_viewA, *m_viewB, *m_viewC;

public:
    explicit NumberView(NumberModel *model, QWidget *parent = nullptr);
};

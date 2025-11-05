#include "numberview.h"
#include <QVBoxLayout>
#include <QIntValidator>

SingleNumberView::SingleNumberView(char valueType, const QString &label, NumberModel *model, QWidget *parent)
    : QWidget(parent), m_model(model), m_valueType(valueType), m_isUpdating(false)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    m_label = new QLabel(label);
    layout->addWidget(m_label);

    m_textEdit = new QLineEdit();
    m_textEdit->setValidator(new QIntValidator(0, 100, this));
    m_textEdit->setMaximumWidth(50);
    layout->addWidget(m_textEdit);

    m_spinBox = new QSpinBox();
    m_spinBox->setRange(0, 100);
    m_spinBox->setMaximumWidth(80);
    layout->addWidget(m_spinBox);

    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(0, 100);
    m_slider->setMaximumWidth(150);
    layout->addWidget(m_slider);

    layout->addStretch();

    connect(m_textEdit, &QLineEdit::editingFinished, this, &SingleNumberView::onTextEditChanged);
    connect(m_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SingleNumberView::onSpinBoxChanged);
    connect(m_slider, &QSlider::valueChanged, this, &SingleNumberView::onSliderChanged);
    connect(m_model, &NumberModel::dataChanged, this, &SingleNumberView::onModelChanged);

    onModelChanged();
}

void SingleNumberView::onModelChanged()
{
    if (m_isUpdating) return;

    m_isUpdating = true;

    int value = 0;
    switch (m_valueType) {
    case 'A': value = m_model->getA(); break;
    case 'B': value = m_model->getB(); break;
    case 'C': value = m_model->getC(); break;
    }

    m_textEdit->setText(QString::number(value));
    m_spinBox->setValue(value);
    m_slider->setValue(value);

    m_isUpdating = false;
}

void SingleNumberView::onTextEditChanged()
{
    if (m_isUpdating) return;

    bool ok;
    int value = m_textEdit->text().toInt(&ok);
    if (ok) {
        applyValueToModel(value);
    } else {
        onModelChanged();
    }
}

void SingleNumberView::onSpinBoxChanged(int value)
{
    if (m_isUpdating) return;
    applyValueToModel(value);
}

void SingleNumberView::onSliderChanged(int value)
{
    if (m_isUpdating) return;
    applyValueToModel(value);
}

void SingleNumberView::applyValueToModel(int value)
{
    m_isUpdating = true;

    switch (m_valueType) {
    case 'A': m_model->setA(value); break;
    case 'B': m_model->setB(value); break;
    case 'C': m_model->setC(value); break;
    }

    m_isUpdating = false;
}

NumberView::NumberView(NumberModel *model, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("MVC - Три связанных числа");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    m_viewA = new SingleNumberView('A', "A:", model);
    m_viewB = new SingleNumberView('B', "B:", model);
    m_viewC = new SingleNumberView('C', "C:", model);

    mainLayout->addWidget(m_viewA);
    mainLayout->addWidget(m_viewB);
    mainLayout->addWidget(m_viewC);

    QLabel *infoLabel = new QLabel("A ≤ B ≤ C | A,C - разрешающее поведение | B - запрещающее поведение");
    infoLabel->setStyleSheet("color: gray; font-size: 10px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
}

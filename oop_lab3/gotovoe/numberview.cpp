#include "numberview.h"
#include <QVBoxLayout>
#include <QIntValidator>
#include <QDebug>

SingleNumberView::SingleNumberView(char valueType, const QString &label, NumberModel *model, QWidget *parent)
    : QWidget(parent), m_model(model), m_valueType(valueType), m_isUpdating(false)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    m_label = new QLabel(label);
    m_label->setFixedWidth(20);
    layout->addWidget(m_label);

    m_textEdit = new QLineEdit();
    m_textEdit->setValidator(new QIntValidator(0, 100, this));
    m_textEdit->setFixedWidth(50);
    m_textEdit->setAlignment(Qt::AlignCenter);
    connect(m_textEdit, &QLineEdit::editingFinished, this, &SingleNumberView::onTextEditChanged);
    layout->addWidget(m_textEdit);

    m_spinBox = new QSpinBox();
    m_spinBox->setRange(0, 100);
    m_spinBox->setFixedWidth(80);
    connect(m_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SingleNumberView::onSpinBoxChanged);
    layout->addWidget(m_spinBox);

    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(0, 100);
    m_slider->setFixedWidth(150);
    connect(m_slider, &QSlider::valueChanged, this, &SingleNumberView::onSliderChanged);
    layout->addWidget(m_slider);

    // ВАЖНО: Подключаем сигнал модели к слоту этого виджета
    connect(m_model, &NumberModel::dataChanged, this, &SingleNumberView::onModelChanged);

    // Первоначальное обновление
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

    // Обновляем ВСЕ элементы управления этого представления
    updateAllControls(value);

    m_isUpdating = false;
}

void SingleNumberView::updateAllControls(int value)
{
    m_textEdit->setText(QString::number(value));
    m_spinBox->setValue(value);
    m_slider->setValue(value);
}

void SingleNumberView::onTextEditChanged()
{
    if (m_isUpdating) return;

    QString text = m_textEdit->text();
    if (text.isEmpty()) {
        // Если поле пустое - восстанавливаем значение
        onModelChanged();
        return;
    }

    bool ok;
    int value = text.toInt(&ok);
    if (ok && value >= 0 && value <= 100) {
        // ВРЕМЕННО блокируем обновления и обновляем ВСЕ элементы этого представления
        m_isUpdating = true;
        updateAllControls(value);  // Сначала синхронизируем элементы между собой
        m_isUpdating = false;

        // Затем применяем значение к модели
        applyValueToModel(value);
    } else {
        // Некорректный ввод - восстанавливаем значение
        onModelChanged();
    }
}

void SingleNumberView::onSpinBoxChanged(int value)
{
    if (m_isUpdating) return;

    // ВРЕМЕННО блокируем обновления и обновляем ВСЕ элементы этого представления
    m_isUpdating = true;
    updateAllControls(value);  // Сначала синхронизируем элементы между собой
    m_isUpdating = false;

    // Затем применяем значение к модели
    applyValueToModel(value);
}

void SingleNumberView::onSliderChanged(int value)
{
    if (m_isUpdating) return;

    // ВРЕМЕННО блокируем обновления и обновляем ВСЕ элементы этого представления
    m_isUpdating = true;
    updateAllControls(value);  // Сначала синхронизируем элементы между собой
    m_isUpdating = false;

    // Затем применяем значение к модели
    applyValueToModel(value);
}

// void SingleNumberView::applyValueToModel(int value)
// {
//     if (m_isUpdating) return;
//
//     // Временно блокируем обновления
//     m_isUpdating = true;
//
//     switch (m_valueType) {
//     case 'A': m_model->setA(value); break;
//     case 'B': m_model->setB(value); break;
//     case 'C': m_model->setC(value); break;
//     }
//
//     m_isUpdating = false;
// }

void SingleNumberView::applyValueToModel(int value)
{
    if (m_isUpdating) return;

    // Временно блокируем обновления только для этого виджета
    // Но разрешаем модели уведомлять другие виджеты
    m_isUpdating = true;

    switch (m_valueType) {
    case 'A':
        m_model->setA(value);
        break;
    case 'B':
        m_model->setB(value);
        break;
    case 'C':
        m_model->setC(value);
        break;
    }

    m_isUpdating = false;

    // После применения значения к модели:
    // 1. Модель проверяет ограничения и может изменить другие значения
    // 2. Модель испускает сигнал dataChanged()
    // 3. ВСЕ SingleNumberView получают этот сигнал и обновляются
}

NumberView::NumberView(NumberModel *model, QWidget *parent)
    : QWidget(parent), m_model(model)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Лабораторная работа 3 - MVC");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QLabel *subtitleLabel = new QLabel("MVC - Три связанных числа");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);

    mainLayout->addSpacing(20);

    m_viewA = new SingleNumberView('A', "A:", model);
    m_viewB = new SingleNumberView('B', "B:", model);
    m_viewC = new SingleNumberView('C', "C:", model);

    mainLayout->addWidget(m_viewA);
    mainLayout->addWidget(m_viewB);
    mainLayout->addWidget(m_viewC);

    // Отладочная информация - УВЕЛИЧИВАЕМ РАЗМЕР
    m_debugLabel = new QLabel();
    m_debugLabel->setStyleSheet("color: blue; font-size: 14px; font-weight: bold; background-color: #f0f0f0; padding: 8px; border: 1px solid #ccc;");
    m_debugLabel->setAlignment(Qt::AlignCenter);
    m_debugLabel->setMinimumHeight(40); // Делаем высоту побольше
    mainLayout->addWidget(m_debugLabel);

    QLabel *infoLabel = new QLabel("A ≤ B ≤ C | A,C - разрешающее поведение | B - запрещающее поведение");
    infoLabel->setStyleSheet("color: gray; font-size: 10px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);

    // Подключаем сигнал модели
    connect(m_model, &NumberModel::dataChanged, this, &NumberView::onModelChanged);

    // Первоначальное обновление
    onModelChanged();
}

void NumberView::onModelChanged()
{
    // Обновляем отладочную информацию с увеличенным шрифтом
    QString debugText = QString("Обновления модели: %1 | A=%2 B=%3 C=%4")
                         .arg(m_model->getUpdateCount())
                         .arg(m_model->getA())
                         .arg(m_model->getB())
                         .arg(m_model->getC());

    m_debugLabel->setText(debugText);

    qDebug() << debugText; // Также выводим в консоль для отладки
}

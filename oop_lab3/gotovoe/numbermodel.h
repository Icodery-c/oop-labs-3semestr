#pragma once

#include <QObject>
#include <QSettings>

class NumberModel : public QObject
{
    Q_OBJECT

private:
    int m_A, m_B, m_C;

public:
    explicit NumberModel(QObject *parent = nullptr);

    // Геттеры
    int getA() const;
    int getB() const;
    int getC() const;

    // Сеттеры с разным поведением
    void setA(int value);  // Разрешающее поведение
    void setB(int value);  // Запрещающее поведение
    void setC(int value);  // Разрешающее поведение

signals:
    void dataChanged();

private:
    void enforceConstraints();
    void saveToSettings();
    void loadFromSettings();
};

#pragma once

#include <QObject>
#include <QSettings>

class NumberModel : public QObject
{
    Q_OBJECT

private:
    int m_A, m_B, m_C;
    bool m_isChanging;
    int m_updateCount;

public:
    explicit NumberModel(QObject *parent = nullptr);

    // Геттеры
    int getA() const { return m_A; }
    int getB() const { return m_B; }
    int getC() const { return m_C; }

    // Сеттеры
    void setA(int value);
    void setB(int value);
    void setC(int value);

    int getUpdateCount() const { return m_updateCount; }

signals:
    void dataChanged();

private:
    void enforceConstraints();
    void saveToSettings();
    void loadFromSettings();
    bool isValidValue(int value) const;
    void setValuesAtomic(int a, int b, int c);
};

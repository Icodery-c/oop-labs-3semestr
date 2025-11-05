#include "numbermodel.h"
#include <QDebug>

NumberModel::NumberModel(QObject *parent)
    : QObject(parent), m_A(0), m_B(50), m_C(100)
{
    loadFromSettings();
}

int NumberModel::getA() const { return m_A; }
int NumberModel::getB() const { return m_B; }
int NumberModel::getC() const { return m_C; }

void NumberModel::setA(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    if (m_A != value) {
        m_A = value;
        enforceConstraints();
        saveToSettings();
        emit dataChanged();
    }
}

void NumberModel::setB(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    if (value >= m_A && value <= m_C) {
        if (m_B != value) {
            m_B = value;
            saveToSettings();
            emit dataChanged();
        }
    }
}

void NumberModel::setC(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    if (m_C != value) {
        m_C = value;
        enforceConstraints();
        saveToSettings();
        emit dataChanged();
    }
}

void NumberModel::enforceConstraints()
{
    if (m_A > m_B) m_B = m_A;
    if (m_C < m_B) m_B = m_C;
    if (m_A > m_C) {
        m_C = m_A;
        m_B = m_A;
    }
}

void NumberModel::saveToSettings()
{
    QSettings settings;
    settings.setValue("A", m_A);
    settings.setValue("B", m_B);
    settings.setValue("C", m_C);
}

void NumberModel::loadFromSettings()
{
    QSettings settings;
    m_A = settings.value("A", 0).toInt();
    m_B = settings.value("B", 50).toInt();
    m_C = settings.value("C", 100).toInt();
    enforceConstraints();
}

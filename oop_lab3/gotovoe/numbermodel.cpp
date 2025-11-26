#include "numbermodel.h"
#include <QDebug>

NumberModel::NumberModel(QObject *parent)
    : QObject(parent), m_A(0), m_B(50), m_C(100), m_isChanging(false), m_updateCount(0)
{
    loadFromSettings();
    qDebug() << "Model created. Initial values: A=" << m_A << "B=" << m_B << "C=" << m_C;
}

void NumberModel::setA(int value)
{
    if (m_isChanging) return;

    if (!isValidValue(value)) {
        qDebug() << "Invalid A value:" << value;
        return;
    }

    m_isChanging = true;

    // Сохраняем старые значения
    int oldA = m_A;
    int oldB = m_B;
    int oldC = m_C;

    // Устанавливаем новое значение A
    m_A = value;

    // РАЗРЕШАЮЩЕЕ поведение - применяем ограничения
    enforceConstraints();

    // Проверяем, действительно ли что-то изменилось
    if (oldA != m_A || oldB != m_B || oldC != m_C) {
        saveToSettings();
        emit dataChanged();
        m_updateCount++;
        qDebug() << "A changed - Final: A=" << m_A << "B=" << m_B << "C=" << m_C;
    }

    m_isChanging = false;
}

void NumberModel::setB(int value)
{
    if (m_isChanging) return;

    if (!isValidValue(value)) {
        qDebug() << "Invalid B value:" << value;
        return;
    }

    // ЗАПРЕЩАЮЩЕЕ поведение - проверяем ограничения
    if (value >= m_A && value <= m_C) {
        if (m_B != value) {
            m_B = value;
            saveToSettings();
            emit dataChanged();
            m_updateCount++;
            qDebug() << "B changed to:" << m_B;
        }
    } else {
        // ЗАПРЕТ - отклоняем изменение
        qDebug() << "B value" << value << "rejected. Must be between" << m_A << "and" << m_C;
    }
}

void NumberModel::setC(int value)
{
    if (m_isChanging) return;

    if (!isValidValue(value)) {
        qDebug() << "Invalid C value:" << value;
        return;
    }

    m_isChanging = true;

    // Сохраняем старые значения
    int oldA = m_A;
    int oldB = m_B;
    int oldC = m_C;

    // Устанавливаем новое значение C
    m_C = value;

    // РАЗРЕШАЮЩЕЕ поведение - применяем ограничения
    enforceConstraints();

    // Проверяем, действительно ли что-то изменилось
    if (oldA != m_A || oldB != m_B || oldC != m_C) {
        saveToSettings();
        emit dataChanged();
        m_updateCount++;
        qDebug() << "C changed - Final: A=" << m_A << "B=" << m_B << "C=" << m_C;
    }

    m_isChanging = false;
}

void NumberModel::enforceConstraints()
{
    bool changed = false;

    // Применяем правило A <= B <= C
    if (m_A > m_B) {
        m_B = m_A;
        changed = true;
        qDebug() << "Enforced: B adjusted to A =" << m_B;
    }

    if (m_B > m_C) {
        m_C = m_B;
        changed = true;
        qDebug() << "Enforced: C adjusted to B =" << m_C;
    }

    if (m_A > m_C) {
        m_C = m_A;
        m_B = m_A;
        changed = true;
        qDebug() << "Enforced: B and C adjusted to A =" << m_A;
    }
}

bool NumberModel::isValidValue(int value) const
{
    return (value >= 0 && value <= 100);
}

void NumberModel::setValuesAtomic(int a, int b, int c)
{
    if (m_isChanging) return;

    m_isChanging = true;

    m_A = a;
    m_B = b;
    m_C = c;

    enforceConstraints();

    m_isChanging = false;
    emit dataChanged();
    m_updateCount++;
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

    // Применяем ограничения после загрузки
    enforceConstraints();
}

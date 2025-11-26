#include "mystorage.h"
#include "ccircle.h"

MyStorage::MyStorage() {}

MyStorage::~MyStorage()
{
    for (CCircle* p : m_data) delete p;
    m_data.clear();
}

void MyStorage::add(CCircle* c)
{
    m_data.append(c);
}

int MyStorage::size() const { return m_data.size(); }
CCircle* MyStorage::at(int index) const { return m_data.at(index); }

void MyStorage::removeAt(int index)
{
    if (index < 0 || index >= m_data.size()) return;
    delete m_data[index];
    m_data.remove(index);
}

void MyStorage::removeSelected()
{
    // remove all selected items
    for (int i = m_data.size() - 1; i >= 0; --i) {
        if (m_data[i]->isSelected()) {
            delete m_data[i];
            m_data.remove(i);
        }
    }
}

void MyStorage::clearSelection()
{
    for (CCircle* c : m_data) c->setSelected(false);
}

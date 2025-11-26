#include "mainwindow.h"
#include "ccircle.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("LR3 - Circles on Form");
    // enable keyboard focus to receive Del key
    setFocusPolicy(Qt::StrongFocus);

    // start with some initial circles (optional)
    // m_storage.add(new CCircle(100,100, m_defaultRadius));
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    painter.fillRect(rect(), Qt::white);

    // draw all circles
    for (int i = 0; i < m_storage.size(); ++i) {
        CCircle* c = m_storage.at(i);
        c->draw(painter);
    }
}

// --- Updated mousePressEvent: select ALL hit circles (default) ---
// Original code preserved below in comments.
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    int x = event->pos().x();
    int y = event->pos().y();
    bool ctrl = (event->modifiers() & Qt::ControlModifier);

    // Clear selection if Ctrl not held
    if (!ctrl) m_storage.clearSelection();

    // NEW: Select ALL circles under pointer ----------------------------------
    for (int i = 0; i < m_storage.size(); ++i) {
        CCircle* c = m_storage.at(i);
        if (c->isInside(x, y)) {
            c->setSelected(true);
        }
    }

    // If none were hit — create new circle
    bool anyHit = false;
    for (int i = 0; i < m_storage.size(); ++i)
        if (m_storage.at(i)->isSelected()) anyHit = true;

    if (!anyHit) {
        CCircle* c = new CCircle(x, y, m_defaultRadius);
        m_storage.add(c);
        c->setSelected(true);
    }

    update();

    /* ---------------- ORIGINAL BEHAVIOR (topmost only) ----------------
    int hitIndex = -1;
    for (int i = m_storage.size() - 1; i >= 0; --i) {
        CCircle* c = m_storage.at(i);
        if (c->isInside(x, y)) { hitIndex = i; break; }
    }
    if (hitIndex == -1) { ... }
    else { ... }
    ------------------------------------------------------------------- */
} // trigger repaint


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        m_storage.removeSelected();
        update();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    update();
}

// --- NEW: change radius using mouse wheel ---
void MainWindow::wheelEvent(QWheelEvent *event)
{
    int x = event->position().x();
    int y = event->position().y();

    for (int i = 0; i < m_storage.size(); ++i) {
        CCircle* c = m_storage.at(i);
        if (c->isInside(x, y)) {
            int delta = event->angleDelta().y() > 0 ? 3 : -3;
            int newR = std::max(5, c->radius() + delta);
            c->setRadius(newR);
        }
    }

    update();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QSpinBox>
#include <QProgressBar>
#include <QTimer>
#include <QMenuBar>
#include <QTabWidget>
#include <QListWidget>
#include <QSlider>
#include <QEvent>
#include "aboutwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onButtonClicked();
    void onTimerTick();
    void openAboutWindow();

private:
    QPushButton *mainButton;
    QLabel *infoLabel;
    QLineEdit *inputField;
    QCheckBox *checkBox;
    QRadioButton *radio1;
    QRadioButton *radio2;
    QComboBox *comboBox;
    QSpinBox *spinBox;
    QProgressBar *progressBar;
    QTimer *timer;
    QTabWidget *tabs;
    QListWidget *listWidget;
    QSlider *slider;
    AboutWindow *aboutWin;
    int progressValue = 0;
};

#endif // MAINWINDOW_H

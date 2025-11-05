#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);
    setWindowTitle("Лабораторная работа №1 — Кнопки и Формы");

    // Главное меню
    QMenu *menuFile = menuBar()->addMenu("Файл");
    QAction *aboutAction = menuFile->addAction("О программе");
    QAction *exitAction = menuFile->addAction("Выход");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::openAboutWindow);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    mainButton = new QPushButton("Нажми меня");
    infoLabel = new QLabel("Информация появится здесь");
    inputField = new QLineEdit();
    checkBox = new QCheckBox("Включить опцию");
    radio1 = new QRadioButton("Вариант 1");
    radio2 = new QRadioButton("Вариант 2");
    comboBox = new QComboBox();
    comboBox->addItems({"Красный", "Зелёный", "Синий"});
    spinBox = new QSpinBox();
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    listWidget = new QListWidget();
    listWidget->addItems({"Элемент A", "Элемент B", "Элемент C"});
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    tabs = new QTabWidget();
    QWidget *tab1 = new QWidget();
    QWidget *tab2 = new QWidget();
    tabs->addTab(tab1, "Вкладка 1");
    tabs->addTab(tab2, "Вкладка 2");

    mainLayout->addWidget(mainButton);
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(inputField);
    mainLayout->addWidget(checkBox);
    mainLayout->addWidget(radio1);
    mainLayout->addWidget(radio2);
    mainLayout->addWidget(comboBox);
    mainLayout->addWidget(spinBox);
    mainLayout->addWidget(progressBar);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(slider);
    mainLayout->addWidget(tabs);

    // Таймер
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);
    timer->start(1000);

    // События
    connect(mainButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(slider, &QSlider::valueChanged, progressBar, &QProgressBar::setValue);
    connect(comboBox, &QComboBox::currentTextChanged, [this](const QString &color){
        infoLabel->setText("Выбран цвет: " + color);
    });
}

MainWindow::~MainWindow() = default;

void MainWindow::onButtonClicked()
{
    infoLabel->setText("Кнопка нажата!");
    progressValue += 10;
    if (progressValue > 100) progressValue = 0;
    progressBar->setValue(progressValue);
}

void MainWindow::onTimerTick()
{
    setWindowTitle("Обновлено: " + QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPushButton *newButton = new QPushButton("Dynamic", this);
    newButton->move(event->pos());
    newButton->show();
    connect(newButton, &QPushButton::clicked, [this, newButton](){
        infoLabel->setText("Создана динамическая кнопка!");
        newButton->setText("OK");
    });
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        infoLabel->setText("Нажата клавиша ПРОБЕЛ");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    infoLabel->setText("Окно изменено: " +
        QString::number(event->size().width()) + "x" +
        QString::number(event->size().height()));
}

void MainWindow::openAboutWindow()
{
    aboutWin = new AboutWindow(this);
    aboutWin->show();
}

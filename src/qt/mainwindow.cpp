#include <QtWidgets/QPushButton>
#include <QApplication>
#include <QDirIterator>
#include <QString>

#include <iostream>

#include <cstring>
#include <unistd.h>

#include "mainwindow.hpp"

#include "common.h"

MainWindow::MainWindow(char** pargv)
    : QMainWindow(nullptr)
{
    argv = pargv;

    this->resize(258, 232);
    this->centralwidget = new QWidget(this);
    this->verticalLayout = new QVBoxLayout(centralwidget);
    this->setCentralWidget(centralwidget);

    char* prgm = argv[0] + strlen(argv[0]);

    while (*(prgm-1) != SEPERATOR) --prgm;

    QDirIterator it(".", {"*" EXE}, QDir::Files);
    while (it.hasNext())
    {
        it.next(); // we want the filename so lets ignore the output
        QString filename = it.fileName();

        if (!isExe(filename.toStdString().c_str()) || filename.compare(prgm) == 0) continue;

        QFile file(filename);
        addButton(file.fileName());

    }
}

void MainWindow::addButton(const QString name)
{
    QPushButton* button = new QPushButton(this->centralwidget);
    button->setText(name);

    connect(button, &QPushButton::clicked, this, [=]{replaceProcess(name);});

    this->verticalLayout->addWidget(button);
}

void MainWindow::replaceProcess(QString name)
{
    execvp(name.toStdString().c_str(), this->argv);
}

MainWindow::~MainWindow()
{
}


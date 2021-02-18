#include <QtWidgets/QPushButton>
#include <QApplication>
#include <QDirIterator>
#include <QString>

#include <iostream>

#include <cerrno>
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

    this->prgm = argv[0] + strlen(argv[0]);

    while (*(this->prgm-1) != SEPERATOR && this->prgm > argv[0]) --this->prgm;

    QDirIterator it(".", {"*" EXE}, QDir::Files);
    while (it.hasNext())
    {
        it.next(); // we want the filename so lets ignore the output
        QString filename = it.fileName();

        if (!isExe(filename.toStdString().c_str()) || filename.compare(prgm) == 0) continue;

        addButton(filename);

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
    // variable length stack arrays are forbidden
    // too bad
    char exec[strlen(this->argv[0]) - strlen(this->prgm) + name.size()];
    strcpy(exec, this->argv[0]);
    strcpy(exec+(this->prgm-this->argv[0]), name.toStdString().c_str());
    this->argv[0] = exec;

    if (execvp(exec, this->argv) == -1)
        printf("execvp() %s\n", strerror(errno));
}

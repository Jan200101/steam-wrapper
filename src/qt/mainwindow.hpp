#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(char**);

    void addButton(QString);

private:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;

    char** argv;
    char* prgm;

public slots:
	void replaceProcess(QString);
};
#endif // MAINWINDOW_HPP

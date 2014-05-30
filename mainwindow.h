#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "getweatherasjson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    // it is important to declare a Q_OBJECT here, otherwise signals & slots won't work
    Q_OBJECT
public slots:
    void myButtonClicked();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public  slots:
    void updateWeaterModel(Weather *weather);

private slots:
    void updateTimeField();
    
private:
    Ui::MainWindow *ui;
    GetWeatherAsJson getWeatherAsJson;
    //void updateIcon(QString code);
};

#endif // MAINWINDOW_H

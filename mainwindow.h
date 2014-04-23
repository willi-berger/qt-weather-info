#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "getweatherasjson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void myButtonClicked();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public  slots:
    void updateWeaterModel(Weather *weather);
    
private:
    Ui::MainWindow *ui;

    GetWeatherAsJson getWeatherAsJson;

};

#endif // MAINWINDOW_H

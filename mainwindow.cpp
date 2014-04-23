#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jsonparse.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->myPushButton, SIGNAL(clicked()), SLOT(myButtonClicked()));
    connect(&getWeatherAsJson, SIGNAL(weatherInfoParsed(Weather*)), this, SLOT(updateWeaterModel(Weather*)));

    // trigger initial load of weather data
    ui->myPushButton->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myButtonClicked()
{
    ui->tfTemp->setText("");
    ui->tfHumidiy->setText("");
    ui->tfPressure->setText("");
    ui->tfWeatherText->setText("");
    ui->lblCode->setText("");

    qDebug("MyButton clicked %s", qPrintable(ui->tfTemp->text()));
    getWeatherAsJson.makeGETRequestForWeather();
}

void MainWindow::updateWeaterModel(Weather *weather)
{
    qDebug() << "updateWeaterModel";

    ui->tfTemp->setText(weather->currentWeather->temp);
    ui->tfHumidiy->setText(weather->currentWeather->humidity);
    ui->tfPressure->setText(weather->currentWeather->pressure);
    ui->tfWeatherText->setText(weather->currentWeather->weatherText);
    ui->lblCode->setText(weather->currentWeather->weatherCode);
}

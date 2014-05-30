#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    connect(ui->btnRefresh, SIGNAL(clicked()), SLOT(myButtonClicked()));
    connect(&getWeatherAsJson, SIGNAL(weatherInfoParsed(Weather*)), this, SLOT(updateWeaterModel(Weather*)));

    // trigger initial load of weather data
    ui->btnRefresh->click();


    // start timer for clock display
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeField()));
    timer->start(1000);

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

    qDebug("MyButton clicked %s", qPrintable(ui->tfTemp->text()));
    getWeatherAsJson.makeGETRequestForWeather();
}


QImage dayIconForCode(QString code)
{
    //TODO add icons and codes
    QString gif;
    switch (code.toInt()) {
    default:
    case 0:     gif="Sunny.gif";break;
    case 1:     gif="PartlyCloudyDay.gif";break;
    case 2:     gif="Cloudy.gif";break;
    case 3:     gif="Overcast.gif";break;
    case 10:	gif="Mist.gif";break;
    case 21:	gif="OccLightRain.gif";break;
    case 22:	gif="IsoSleetSwrsDay.gif";break;
    case 23:	gif="OccLightSleet.gif";break;
    case 24:	gif="FreezingDrizzle.gif";break;
    case 29:	gif="PartCloudRainThunderDay.gif";break;
    case 38:	gif="ModSnow.gif";break;
    case 39:	gif="Blizzard.gif";break;
    case 45:	gif="Fog.gif";break;
    case 49:	gif="FreezingFog.gif";break;
    case 50:	gif="IsoRainSwrsDay.gif";break;
    case 51:	gif="OccLightRain.gif";break;
    case 56:	gif="FreezingDrizzle.gif";break;
    case 57:	gif="FreezingDrizzle.gif";break;
    case 60:	gif="OccLightRain.gif";break;
    case 61:	gif="ModRain.gif";break;
    case 62:	gif="ModRainSwrsDay.gif";break;
    case 63:	gif="ModRain.gif";break;
    case 64:	gif="HeavyRainSwrsDay.gif";break;
    case 65:	gif="HeavyRain.gif";break;
    case 66:	gif="FreezingRain.gif";break;
    case 67:	gif="FreezingRain.gif";break;
    case 68:	gif="ModSleet.gif";break;
    case 69:	gif="HeavySleet.gif";break;
    case 70:	gif="OccLightSnow.gif";break;
    case 71:	gif="OccLightSnow.gif";break;
    case 72:	gif="ModSnow.gif";break;
    case 73:	gif="ModSnow.gif";break;
    case 74:	gif="HeavySnowSwrsDay.gif";break;
    case 75:	gif="HeavySnow.gif";break;
    case 79:	gif="FreezingRain.gif";break;
    case 80:	gif="IsoRainSwrsDay.gif";break;
    case 81:	gif="ModRainSwrsDay.gif";break;
    case 82:	gif="HeavyRain.gif";break;
    case 83:	gif="ModSleetSwrsDay.gif";break;
    case 84:	gif="ModSleetSwrsDay.gif";break;
    case 85:	gif="IsoSnowSwrsDay.gif";break;
    case 86:	gif="ModSnowSwrsDay.gif";break;
    case 87:	gif="FreezingRain.gif";break;
    case 88:	gif="FreezingRain.gif";break;
    case 91:	gif="PartCloudRainThunderDay.gif";break;
    case 92:	gif="CloudRainThunder.gif";break;
    case 93:	gif="PartCloudSleetSnowThunderDay.gif";break;
    case 94:	gif="CloudSleetSnowThunder.gif";break;
    }

    return QImage(QString("://resources/").append(gif));
}

QImage nightIconForCode(QString code)
{
    //TODO add icons and codes
    QString gif;
    switch (code.toInt()) {
    default:
    case 0	:     gif="Clear.gif";break;
    case 1	:     gif="PartlyCloudyNight.gif";break;
    case 2	:     gif="Cloudy.gif";break;
    case 3	:     gif="Overcast.gif";break;
    case 10	:     gif="Mist.gif";break;
    case 21	:     gif="OccLightRain.gif";break;
    case 22	:     gif="IsoSleetSwrsNight.gif";break;
    case 23	:     gif="OccLightSleet.gif";break;
    case 24	:     gif="FreezingDrizzle.gif";break;
    case 29	:     gif="PartCloudRainThunderNight.gif";break;
    case 38	:     gif="ModSnow.gif";break;
    case 39	:     gif="Blizzard.gif";break;
    case 45	:     gif="Fog.gif";break;
    case 49	:     gif="FreezingFog.gif";break;
    case 50	:     gif="IsoRainSwrsNight.gif";break;
    case 51	:     gif="OccLightRain.gif";break;
    case 56	:     gif="FreezingDrizzle.gif";break;
    case 57	:     gif="FreezingDrizzle.gif";break;
    case 60	:     gif="OccLightRain.gif";break;
    case 61	:     gif="ModRain.gif";break;
    case 62	:     gif="ModRainSwrsNight.gif";break;
    case 63	:     gif="ModRain.gif";break;
    case 64	:     gif="HeavyRainSwrsNight.gif";break;
    case 65	:     gif="HeavyRain.gif";break;
    case 66	:     gif="FreezingRain.gif";break;
    case 67	:     gif="FreezingRain.gif";break;
    case 68	:     gif="ModSleet.gif";break;
    case 69	:     gif="HeavySleet.gif";break;
    case 70	:     gif="OccLightSnow.gif";break;
    case 71	:     gif="OccLightSnow.gif";break;
    case 72	:     gif="ModSnow.gif";break;
    case 73	:     gif="ModSnow.gif";break;
    case 74	:     gif="HeavySnowSwrsNight.gif";break;
    case 75	:     gif="HeavySnow.gif";break;
    case 79	:     gif="FreezingRain.gif";break;
    case 80	:     gif="IsoRainSwrsNight.gif";break;
    case 81	:     gif="ModRainSwrsNight.gif";break;
    case 82	:     gif="HeavyRain.gif";break;
    case 83	:     gif="ModSleetSwrsNight.gif";break;
    case 84	:     gif="ModSleetSwrsNight.gif";break;
    case 85	:     gif="IsoSnowSwrsNight.gif";break;
    case 86	:     gif="ModSnowSwrsNight.gif";break;
    case 87	:     gif="FreezingRain.gif";break;
    case 88	:     gif="FreezingRain.gif";break;
    case 91	:     gif="PartCloudRainThunderNight.gif";break;
    case 92	:     gif="CloudRainThunder.gif";break;
    case 93	:     gif="PartCloudSleetSnowThunderNight.gif";break;
    case 94	:     gif="CloudSleetSnowThunder.gif";break;
    }

    return QImage(QString("://resources/").append(gif));
}


void MainWindow::updateWeaterModel(Weather *weather)
{
    qDebug() << "updateWeaterModel";

    // today
    ui->tfTemp->setText(weather->current->temp);
    ui->tfHumidiy->setText(weather->current->humidity);
    ui->tfPressure->setText(weather->current->pressure);
    ui->tfWeatherText->setText(weather->current->weatherText);
    WindInfo *windInfo = weather->current->windInfo;
    ui->tfWind->setText(windInfo->speed.append(" ").append(windInfo->windUnit).append(" ").append(windInfo->dir));

    ui->iconToday->setPixmap(
        QPixmap::fromImage(
            QTime::currentTime().hour() > 18 ?
                  dayIconForCode(weather->current->weatherCode) :
                  dayIconForCode(weather->current->weatherCode)));


    // tomorrow
    {
        ui->tfTempMaxDay1->setText(weather->day1->dayMaxTemp);
        ui->tfTempMinNight1->setText(weather->day1->nightMinTemp);
        ui->tfWeatherTextDay1->setText(weather->day1->day->weatherText);
        ui->tfWeatherTextNight1->setText(weather->day1->night->weatherText);
        WindInfo *wind1d = weather->day1->day->windInfo;
        ui->tfWindDay1->setText(wind1d->speed.append(" ").append(wind1d->windUnit).append(" ").append(wind1d->dir));
        WindInfo *wind1n = weather->day1->night->windInfo;
        ui->tfWindNight1->setText(wind1n->speed.append(" ").append(wind1n->windUnit).append(" ").append(wind1n->dir));
        ui->iconDay1->setPixmap(QPixmap::fromImage(dayIconForCode(weather->day1->day->weatherCode)));
        ui->iconNight1->setPixmap(QPixmap::fromImage(nightIconForCode(weather->day1->night->weatherCode)));
    }

    // after tomorrow
    {
        ui->tfTempMaxDay2->setText(weather->day2->dayMaxTemp);
        ui->tfTempMinNight2->setText(weather->day2->nightMinTemp);
        ui->tfWeatherTextDay2->setText(weather->day2->day->weatherText);
        ui->tfWeatherTextNight2->setText(weather->day2->night->weatherText);
        WindInfo *wind1d = weather->day2->day->windInfo;
        ui->tfWindDay2->setText(wind1d->speed.append(" ").append(wind1d->windUnit).append(" ").append(wind1d->dir));
        WindInfo *wind1n = weather->day2->night->windInfo;
        ui->tfWindNight2->setText(wind1n->speed.append(" ").append(wind1n->windUnit).append(" ").append(wind1n->dir));
        ui->iconDay2->setPixmap(QPixmap::fromImage(dayIconForCode(weather->day2->day->weatherCode)));
        ui->iconNight2->setPixmap(QPixmap::fromImage(nightIconForCode(weather->day2->night->weatherCode)));
    }

    // free memory !!!
    delete weather;
}

void MainWindow::updateTimeField()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';

    ui->lblTime->setText(text);
}

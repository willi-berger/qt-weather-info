#ifndef GETWEATHERASJSON_H
#define GETWEATHERASJSON_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include "weatherinfo.h"

class GetWeatherAsJson :  public QObject
{
    Q_OBJECT

public:
    explicit GetWeatherAsJson(QObject *parent = 0);

    void makeGETRequestForWeather();


signals:
    void weatherInfoParsed(Weather *weather);

public  slots:
    void parseNetworkResponse(QNetworkReply* qNetworkReply);



private:
    static const char*  URL;

    QNetworkAccessManager qNetworkAccessManager;
};

#endif // GETWEATHERASJSON_H

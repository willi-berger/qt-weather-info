
#include "getweatherasjson.h"
#include <qjson/parser.h>
#include "weatherinfo.h"

GetWeatherAsJson::GetWeatherAsJson(QObject *parent): QObject(parent)
{
    QObject::connect(&qNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
}




const QString kBaseUrl = "http://www.myweather2.com/developer/forecast.ashx?uac=uiHtkqrLhk&query=46.76,14.36&temp_unit=c&output=json";


void GetWeatherAsJson::makeGETRequestForWeather()
{
    qDebug("makeGETRequestForWeather");
    // TODO how can we nest these three initializations ?
    QUrl url ( kBaseUrl );
    QNetworkRequest req ( url );
    qNetworkAccessManager.get(req);
}

/**
{ "weather":
    {
        "curren_weather":
            [ {"humidity": "87", "pressure": "1009", "temp": "9", "temp_unit": "c", "weather_code": "61", "weather_text": "Rain, Light Rain",
                "wind": [ {"dir": "NW", "speed": "2", "wind_unit": "kph" } ] } ],
        "forecast":
        [
                {
                "date": "2014-04-20",
                "day": [ {"weather_code": "60", "weather_text": "Patchy light rain",
                    "wind": [ {"dir": "E", "dir_degree": "93", "speed": "7", "wind_unit": "kph" } ] } ], "day_max_temp": "11",
                "night": [ {"weather_code": "45", "weather_text": "Fog",
                "wind": [ {"dir": "SSW", "dir_degree": "196", "speed": "4", "wind_unit": "kph" } ] } ], "night_min_temp": "4",
                "temp_unit": "c" },
                {
                "date": "2014-04-21",
                "day": [ {"weather_code": "61", "weather_text": "Light rain",
                    "wind": [ {"dir": "SSW", "dir_degree": "204", "speed": "7", "wind_unit": "kph" } ] } ], "day_max_temp": "14",
                "night": [ {"weather_code": "45", "weather_text": "Fog",
                    "wind": [ {"dir": "WSW", "dir_degree": "255", "speed": "7", "wind_unit": "kph" } ] } ], "night_min_temp": "4", "temp_unit": "c"
                }
        ]
    }
}
*/

void GetWeatherAsJson::parseNetworkResponse(QNetworkReply* qNetworkReply)
{
    qDebug() << ">>>>>parseNetworkResponse<<<<<<<<<<<<<<<";
    QByteArray data = qNetworkReply->readAll();

    /*
     *{ "type": "success", "value": { "id": 242, "joke": "Everybody loves Raymond. Except Chuck Norris.", "categories": [] } }
     */
    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse (data, &ok).toMap();

    Weather *weather = new Weather();
    WeatherInfo *currentInfo = new WeatherInfo();
    weather->currentWeather = currentInfo;

    if ( ok )
    {
        QVariantMap  weather = result["weather"].toMap();
        QVariantList current_weather_list = weather["curren_weather"].toList();
        QVariantMap  current_weather = current_weather_list[0].toMap();
        currentInfo->temp = current_weather["temp"].toString();
        currentInfo->humidity = current_weather["humidity"].toString();
        currentInfo->pressure = current_weather["pressure"].toString();
        currentInfo->weatherText = current_weather["weather_text"].toString();
        currentInfo->weatherCode = current_weather["weather_code"].toString();
    }

    qDebug() << "temp: " << currentInfo->temp;
    emit weatherInfoParsed(weather);
}



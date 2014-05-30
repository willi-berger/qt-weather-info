
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

WeatherInfo* parseWeatherInfo(QVariantMap weather_info_map)
{
    WeatherInfo *weatherInfo = new WeatherInfo();

    weatherInfo->temp   = weather_info_map["temp"].toString();
    weatherInfo->humidity = weather_info_map["humidity"].toString();
    weatherInfo->pressure = weather_info_map["pressure"].toString();
    weatherInfo->weatherText = weather_info_map["weather_text"].toString();
    weatherInfo->weatherCode = weather_info_map["weather_code"].toString();

    QVariantList wind_list = weather_info_map["wind"].toList();
    QVariantMap wind_map = wind_list[0].toMap();
    weatherInfo->windInfo = new WindInfo();
    weatherInfo->windInfo->dir = wind_map["dir"].toString();
    weatherInfo->windInfo->dirDegree = wind_map["dir_degree"].toString();
    weatherInfo->windInfo->speed = wind_map["speed"].toString();
    weatherInfo->windInfo->windUnit = wind_map["wind_unit"].toString();

    return weatherInfo;
}

void GetWeatherAsJson::parseNetworkResponse(QNetworkReply* qNetworkReply)
{
    qDebug() << ">>>>>parseNetworkResponse<<<<<<<<<<<<<<<";
    QByteArray data = qNetworkReply->readAll();
    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse (data, &ok).toMap();

    if ( ok )
    {
        Weather* weather = new Weather();

        // current_weather
        QVariantMap  weather_map = result["weather"].toMap();
        QVariantMap  current_weather = weather_map["curren_weather"].toList()[0].toMap();
        weather->current = parseWeatherInfo(current_weather);

        {
            // forecast 0
            QVariantMap forecast = weather_map["forecast"].toList()[0].toMap();
            weather->day1 = new ForeCast();
            weather->day1->date = forecast["date"].toString();
            weather->day1->dayMaxTemp = forecast["day_max_temp"].toString();
            //QVariantList forecast_day_list = forecast["day"].toList();
            weather->day1->day = parseWeatherInfo(forecast["day"].toList()[0].toMap());
            weather->day1->nightMinTemp = forecast["night_min_temp"].toString();
            weather->day1->night = parseWeatherInfo(forecast["night"].toList()[0].toMap());
        }
        {
            // forecast 1
            QVariantMap forecast = weather_map["forecast"].toList()[1].toMap();
            weather->day2 = new ForeCast();
            weather->day2->date = forecast["date"].toString();
            weather->day2->dayMaxTemp = forecast["day_max_temp"].toString();
            weather->day2->day = parseWeatherInfo(forecast["day"].toList()[0].toMap());
            weather->day2->nightMinTemp = forecast["night_min_temp"].toString();
            weather->day2->night = parseWeatherInfo(forecast["night"].toList()[0].toMap());
        }



        qDebug() << "temp: " << weather->current->temp;
        emit weatherInfoParsed(weather);
    }
    qNetworkReply->deleteLater();
}



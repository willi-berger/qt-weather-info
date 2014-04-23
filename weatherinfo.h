#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QObject>


/**
  http://www.myweather2.com/developer/forecast.ashx?uac=uiHtkqrLhk&query=46.76,14.36&temp_unit=c&output=json
  */
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

class WeatherInfo
{

public:
    QString humidity;
    QString pressure;
    QString temp;
    QString tempUnit;
    QString weatherCode;
    QString weatherText;
    // TODO to be continued
    WeatherInfo();
};


class Weather
{

public:
    WeatherInfo *currentWeather;
    Weather();

};

#endif // WEATHERINFO_H

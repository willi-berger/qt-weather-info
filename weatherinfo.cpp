#include "weatherinfo.h"
#include "qdebug.h"

ForeCast::ForeCast()
{
}

ForeCast::~ForeCast()
{
    delete day;
    delete night;
}

WeatherInfo::WeatherInfo()
{
}

WeatherInfo::~WeatherInfo()
{
    qDebug() << "WeatherInfo::~WeatherInfo()";
    delete windInfo;
}

Weather::Weather()
{
    //buf = new char[1000000];
}

Weather::~Weather()
{
    qDebug() << "Weather::~Weather()";
    delete current;
}

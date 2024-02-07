//
// Created by Святослав on 11.02.2024.
//
#include <iostream>
#ifndef INC_7WEATHER_BIN_FORECAST_H_
#define INC_7WEATHER_BIN_FORECAST_H_
#pragma once

class Day {

    struct Date{
      int DateOfMonth;
      std::string Month;
      int Year;
    };

    struct TimePeriod {
        std::string TimePeriodName;
        std::string Weather_type;
        int Temperature; // Средняя температура в течение указанного периода
        int WindMoveSpeed; //  Скорость ветра
        int WindDir; // Направление ветра
        int Visibility; // Видимость в км
        int Fallout; // Осадки в мм
        std::string Painting; // Логотип
    };

    void DayRender();

};

#endif //INC_7WEATHER_BIN_FORECAST_H_

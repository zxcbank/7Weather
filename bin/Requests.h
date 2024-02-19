//
// Created by Святослав on 12.02.2024.
//
#pragma once
#ifndef INC_7WEATHER_BIN_REQUESTS_H_
#define INC_7WEATHER_BIN_REQUESTS_H_
#include <iostream>
#include "ConfigParser.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


class TimePeriod {
 public:
  std::string TimePeriodName;
  int Weather_type;
  int Temperature; // Средняя температура в течение указанного периода
  int WindMoveSpeed; //  Скорость ветра
  int WindDir; // Направление ветра
  int Visibility; // Видимость в км
  int Fallout; // Осадки в мм
  std::string time;
};

class City {
  private:
    std::string CityName;
    float Longitude, Latitude;
 public:
    std::vector<TimePeriod> WeatherData;
    float GetLongitude() const;
    float GetLatitude() const;
    const std::string& GetCityName() const {
      return CityName;
    }
    City (const std::string& CityName_) : CityName(CityName_){};
    City();
    void GetCoords();
};


class AllCitiesForecast {
 public:
  int Period;
  int Frequency;
  const std::vector<City>& GetCitiesData() const {
    return CitiesData;
  }
 public:
    std::vector<City> CitiesData;
    AllCitiesForecast(std::vector<City> CitiesData_, int  F, int P) : CitiesData(CitiesData_), Period(P), Frequency(F){};
    void GetForecast();
};

#endif //INC_7WEATHER_BIN_REQUESTS_H_

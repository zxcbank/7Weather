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

class City {
  private:
    std::string CityName;
    float Longitude, Latitude;
  public:
    const std::string& GetCityName() const {
      return CityName;
    }
    City(const std::string& CityName_) : CityName(CityName_){};
    void GettingCoords();
};

class CitiesCrds{
  private:
    std::vector<City> CitiesData;
  public:
    CitiesCrds(std::vector<City> CitiesData_) : CitiesData(CitiesData_){};
};

#endif //INC_7WEATHER_BIN_REQUESTS_H_

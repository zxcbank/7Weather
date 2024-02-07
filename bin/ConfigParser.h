//
// Created by Святослав on 11.02.2024.
//
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#pragma once

using json = nlohmann::json;

#ifndef INC_7WEATHER_BIN_PARSING_H_
#define INC_7WEATHER_BIN_PARSING_H_

class ConfigParser {
  private:
    std::vector <std::string> Cities;
    int Period; // Days for Forecast
    int Frequency; // hrs for update Forecast

  public:
    const std::vector<std::string>& GetCities() const {
      return Cities;
    }

    int GetPeriod() const {
      return Period;
    }

    int GetFrequency() const {
      return Frequency;
    }

    ConfigParser (const std::string& ConfigFileName) {
      std::ifstream ConfigFile(ConfigFileName);
      json Data = json::parse(ConfigFile);
      std::string Json_String = Data.dump();

      auto Json_Dict = json::parse(Json_String);
      Frequency = Json_Dict["Frequency"];
      Period = Json_Dict["Period"];
      for (int i = 0; i < Json_Dict["Cities"].size(); i++) {
        Cities.push_back(Json_Dict["Cities"][std::to_string(i)]);
      }
    }
};

#endif //INC_7WEATHER_BIN_PARSING_H_
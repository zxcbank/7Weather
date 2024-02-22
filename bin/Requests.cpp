//
// Created by Святослав on 12.02.2024.
//

#include "Requests.h"
#include <cmath>

void City::GetCoords() {
  std::string Ninjas_City_link = "https://api.api-ninjas.com/v1/city";
  std::string Token = "G2RJZtYr/giSjCtdLBBpMw==39GYXHrNepeu021U";
  cpr::Response Data = cpr::Get(cpr::Url{Ninjas_City_link},
                                cpr::Parameters{{"name", CityName}},
                                cpr::Header{{"X-Api-Key" , Token}});
  if (Data.status_code != 200){
    if (Data.status_code == 0) {
      std::cerr << "No Internet connection\n";
    } else {
      std::cerr << "This City was not Found by Ninjas-Api, use english and only current name of city.\n";
    }
    exit(EXIT_FAILURE);
  }
  json Json_City = json::parse(Data.text);
  CityName = Json_City[0]["name"];
  Longitude = Json_City[0]["longitude"]; //
  Latitude = Json_City[0]["latitude"];
}
float City::GetLongitude() const {
  return Longitude;
}
float City::GetLatitude() const {
  return Latitude;
}

void AllCitiesForecast::GetForecast(){
  for (auto& el : CitiesData){
    std::string OMURL = "https://api.open-meteo.com/v1/forecast";
    cpr::Response Data = cpr::Get(cpr::Url{OMURL},
        cpr::Parameters{{"latitude", std::to_string(el.GetLatitude())},
                        {"longitude", std::to_string(el.GetLongitude())},
                        {"hourly", "wind_speed_10m"},
                        {"hourly", "wind_direction_10m"},
                        {"hourly", "weather_code"},
                        {"hourly", "precipitation"},
                        {"hourly", "visibility"},
                        {"timezone", "Europe/Moscow"},
                        {"hourly", "temperature_2m"},
                        {"forecast_days", "15"},
                        {"hourly", "relative_humidity_2m"}});
//    std::cout << "\n----------------\n" << Data.text;
    json mama = json::parse(Data.text);
//    std::cout << "\n----------------\n" << mama["hourly"]["temperature_2m"][0];
    for (int i = 0; i < 60; i++) {
      TimePeriod A;
      A.Weather_type = mama["hourly"]["weather_code"][i * 6];
      A.Temperature = mama["hourly"]["temperature_2m"][i * 6];
      A.WindDir = mama["hourly"]["wind_direction_10m"][i * 6];
      A.WindMoveSpeed = mama["hourly"]["wind_speed_10m"][i * 6];
      A.Visibility = mama["hourly"]["visibility"][i * 6];
      A.Fallout = mama["hourly"]["precipitation"][i * 6];
      A.time = mama["hourly"]["time"][i * 6];
      el.WeatherData.push_back(A);
    }
  }
}

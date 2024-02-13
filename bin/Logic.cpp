//
// Created by Святослав on 12.02.2024.
//

#include "Logic.h"
//#define CONFIGPARSER_DEBUG
//#define REQUESTS_DEBUG
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

void Logic(const std::string& fn){
  ConfigParser a = ConfigParser(fn);

#ifdef CONFIGPARSER_DEBUG
  std::cout << "----------------------\n";
  std::cout << "CONFIGPARSER RESULT: \n";
  std::cout << "period: " << a.GetPeriod() << "\n";
  std::cout << "frequency: " << a.GetFrequency() << "\ncities: ";
  for (auto el : a.GetCities())
    std::cout << el << " ";
  std::cout << "\n----------------------\n";
#endif

  std::vector<City> CitiesData_;
  for (const auto& el : a.GetCities()){
    City tmp = City(el);
    tmp.GetCoords();
    CitiesData_.push_back(tmp);
  }

  AllCitiesForecast MagicWeatherObject = AllCitiesForecast(CitiesData_, a.GetFrequency(), a.GetPeriod());
#ifdef REQUESTS_DEBUG
  for (auto el : MagicWeatherObject.GetCitiesData()){
    std::cout << el.GetCityName() << " shirota: " << el.GetLatitude() << " dolgota: " << el.GetLongitude() << "\n";
  }
#endif
  MagicWeatherObject.GetForecast();


}
//void Render(const AllCitiesForecast& MagicWeatherObject) {
//
//}

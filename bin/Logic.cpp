//
// Created by Святослав on 12.02.2024.
//

#include "Logic.h"
#define CONFIGPARSER_DEBUG

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

  City myCity = City(a.GetCities()[0]);
  myCity.GettingCoords();

}
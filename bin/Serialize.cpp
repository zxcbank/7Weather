//
// Created by Святослав on 19.02.2024.
//

#include "Serialize.h"

std::string serialize_Date(std::string date){
  return date.substr(0, 10);
}
std::string serialize_Fallout(int x){
  return std::to_string(x) + "mm";
}

std::string serialize_Temperature(int x){
  if (x > 0)
    return "+" + std::to_string(x) + "°C \n";
  return std::to_string(x) + "°C \n";
}

std::string seriallize_WindMoveSpeed(int x) {
  return std::to_string(x) + " km/h \n";
}

std::string serialize_WindDirection(int x){
  if ((x <= 23) || (x > 337))
    return "⬆";
  else if (x <= 68)
    return "⬈";
  else if (x <= 113)
    return "⮕";
  else if (x <= 148)
    return "⬊";
  else if (x <= 193)
    return "⬇";
  else if (x <= 238)
    return "⬋";
  else if (x <= 283)
    return "⬅";
  else
    return "⬉";
}

std::string serialize_Visibility(int x){
  return std::to_string(x) + "m\n";
}
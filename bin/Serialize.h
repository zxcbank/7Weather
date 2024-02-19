//
// Created by Святослав on 19.02.2024.
//

#ifndef INC_7WEATHER_BIN_SERIALIZE_H_
#define INC_7WEATHER_BIN_SERIALIZE_H_
#include <iostream>

std::string serialize_Date(std::string date);
std::string serialize_Fallout(int x);
std::string serialize_Temperature(int x);
std::string seriallize_WindMoveSpeed(int x);
std::string serialize_WindDirection(int x);
std::string serialize_Visibility(int x);

#endif //INC_7WEATHER_BIN_SERIALIZE_H_

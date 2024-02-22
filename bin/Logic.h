//
// Created by Святослав on 12.02.2024.
//
#pragma once
#include "ConfigParser.h"
#include "Requests.h"
#include <ftxui/dom/elements.hpp>
#include <ctime>


#ifndef INC_7WEATHER_BIN_LOGIC_H_
#define INC_7WEATHER_BIN_LOGIC_H_
#include "Serialize.h"
#include <ftxui/dom/elements.hpp>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <format>
#include "ftxui/component/event.hpp"

void Logic(const std::string& fn);
auto generate_vbox(City el, int i, int j);
//void Render(const AllCitiesForecast& MagicWeatherObject);

#endif //INC_7WEATHER_BIN_LOGIC_H_

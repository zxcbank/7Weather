//
// Created by Святослав on 12.02.2024.
//

#include "Logic.h"
#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/captured_mouse.hpp"

auto generate_vbox(City el, int i, int j){
  std::string PartDay;
  switch (j){
    case 0:
      PartDay = "Night";
      break;
    case 1:
      PartDay = "Morning";
      break;
    case 2:
      PartDay = "Day";
      break;
    case 3:
      PartDay = "Evening";
      break;
  }
  auto element = ftxui::vbox({
                                 ftxui::text(PartDay) | ftxui::color(ftxui::Color::Red),
                                 ftxui::text(serialize_Temperature(el.WeatherData[i * 4 + j].Temperature))| ftxui::center,
                                 ftxui::text((serialize_WindDirection(el.WeatherData[i * 4 + j].WindDir)
                                     + seriallize_WindMoveSpeed(el.WeatherData[i * 4 + j].WindMoveSpeed)))| ftxui::center,
                                 ftxui::text(serialize_Visibility(el.WeatherData[i * 4 + j].Visibility))| ftxui::center,
                                 ftxui::text(serialize_Fallout(el.WeatherData[i * 4 + j].Fallout)) | ftxui::center,
                             }) | ftxui::borderHeavy;
  return element | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 40);
}

void generate_default(City& el, int P, ftxui::Elements& periodvec) {
  for (int i = 0; i < P; i++) {
    ftxui::Elements dayvec;
    for (int j = 0; j < 4; j++) {
      auto y = generate_vbox(el, i, j);
      dayvec.push_back(y);
    }
    auto day = ftxui::hbox(ftxui::text(serialize_Date(el.WeatherData[i * 4].time)), dayvec);
    periodvec.push_back(day);
  }
}

void generate_day_box(ftxui::Elements& dayvec, City& el, int i){
  for (int j = 0; j < 4; j++) {
    auto y = generate_vbox(el, i, j);
    dayvec.push_back(y);
  }
}

void Logic(const std::string& fn) {
  ConfigParser a = ConfigParser(fn);

  std::vector<City> CitiesData_;
  for (const auto& el : a.GetCities()){
    City tmp = City(el);
    tmp.GetCoords();
    CitiesData_.push_back(tmp);
  }

  AllCitiesForecast MagicWeatherObject = AllCitiesForecast(CitiesData_, a.GetFrequency(), a.GetPeriod());
  MagicWeatherObject.GetForecast();
  //-*--------------------------------------
  auto screen = ftxui::ScreenInteractive::Fullscreen();

  ftxui::Elements periodvec;
  int CityIndex = 0;
  std::vector<ftxui::Event> keys;
  float focus_y = 0.2f;
  float YIncrement = 0.1f;
  screen.TrackMouse(true);

  City el = MagicWeatherObject.GetCitiesData()[CityIndex];
  generate_default(el, MagicWeatherObject.Period, periodvec);

  std::time_t last_time = std::time(nullptr);
  std::time_t cur_time = std::time(nullptr);

  std::thread th1([&](){

    while (true){
        cur_time = std::time(nullptr);
        std::this_thread::sleep_for(std::chrono::seconds(a.GetFrequency()));
        last_time = cur_time;
        MagicWeatherObject.GetForecast();
        periodvec.clear();
        generate_default(el, MagicWeatherObject.Period, periodvec);
      }
    }
  );


  auto renderer = ftxui::Renderer([&] {
    std::time_t cur_time = std::time(nullptr);
    ftxui::Element main_element = ftxui::vbox(ftxui::text(el.GetCityName()) | ftxui::center | ftxui::color(ftxui::Color::Blue),
                                              ftxui::separator(),
                                              periodvec )  | ftxui::focusPositionRelative(0, focus_y) | ftxui::yframe | ftxui::flex;
    return main_element;
  }) ;

  renderer |= ftxui::CatchEvent([&](ftxui::Event LastEvent){
    if (LastEvent == ftxui::Event::Escape){
      exit(EXIT_SUCCESS);
    } else if (LastEvent == ftxui::Event::Special("-") && MagicWeatherObject.Period > 0) {
      --MagicWeatherObject.Period;
      periodvec.pop_back();
      return true;
    } else if (LastEvent == ftxui::Event::Special("+") && MagicWeatherObject.Period < 15) {
      ftxui::Elements dayvec;
      generate_day_box(dayvec, el, MagicWeatherObject.Period);
      auto day = ftxui::hbox(ftxui::text(serialize_Date(el.WeatherData[MagicWeatherObject.Period * 4].time)), dayvec);
      periodvec.push_back(day);
      MagicWeatherObject.Period++;
      return true;
    } else if (LastEvent == ftxui::Event::Special("n") || LastEvent == ftxui::Event::Special("p")) {
      if (LastEvent == ftxui::Event::Special("n")){
        if (CityIndex == CitiesData_.size()-1)
          CityIndex = 0;
        else
          CityIndex++;
      } else if (LastEvent == ftxui::Event::Special("p")){
        if (CityIndex == 0)
          CityIndex = CitiesData_.size()-1;
        else
          CityIndex--;
      }
      periodvec.clear();
      el = MagicWeatherObject.GetCitiesData()[CityIndex];
      generate_default(el, MagicWeatherObject.Period, periodvec);
      return true;
    }
    if (LastEvent.mouse().button == ftxui::Mouse::WheelDown){
      if (focus_y + YIncrement < 1.f)
        focus_y += YIncrement;
      return true;
    }
    if (LastEvent.mouse().button == ftxui::Mouse::WheelUp){
      if (focus_y - YIncrement > 0)
        focus_y -= YIncrement;
      return true;
    }
    return false;
  });

  screen.Loop(renderer);
  th1.join();
}
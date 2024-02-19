//
// Created by Святослав on 12.02.2024.
//

#include "Logic.h"
//#define CONFIGPARSER_DEBUG
//#define REQUESTS_DEBUG

auto generate_vbox(City el, int i, int j){
  auto element = ftxui::vbox({
                                 ftxui::text(serialize_Temperature(el.WeatherData[i * 4 + j].Temperature)),
                                 ftxui::text((serialize_WindDirection(el.WeatherData[i * 4 + j].WindDir)
                                     + seriallize_WindMoveSpeed(el.WeatherData[i * 4 + j].WindMoveSpeed))),
                                 ftxui::text(serialize_Visibility(el.WeatherData[i * 4 + j].Visibility)),
                                 ftxui::text(serialize_Fallout(el.WeatherData[i * 4 + j].Fallout)),
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

void ListeningKeyBoardEvents(AllCitiesForecast& MagicWeatherObject, std::vector<ftxui::Event>& keys, ftxui::Elements& periodvec, int& CityIndex, std::vector<City>& CitiesData_, City& el){
  if (!keys.empty()) {
    auto LastEvent = keys[keys.size() - 1];
    if (LastEvent == ftxui::Event::Escape){
      exit(EXIT_SUCCESS);
    } else if (LastEvent == ftxui::Event::Special("-") && MagicWeatherObject.Period > 0) {
      --MagicWeatherObject.Period;
      std::cout << MagicWeatherObject.Period << "\n";
      periodvec.pop_back();
    } else if (LastEvent == ftxui::Event::Special("+") && MagicWeatherObject.Period < 15) {
      ftxui::Elements dayvec;
      generate_day_box(dayvec, el, MagicWeatherObject.Period);
      auto day = ftxui::hbox(ftxui::text(serialize_Date(el.WeatherData[MagicWeatherObject.Period * 4].time)), dayvec);
      periodvec.push_back(day);
      MagicWeatherObject.Period++;
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
    }
  }
}

void Logic(const std::string& fn){
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
  screen.SetCursor({0, 0, ftxui::Screen::Cursor::Hidden});
  ftxui::Elements periodvec;
  int CityIndex = 0;
  std::vector<ftxui::Event> keys;
  City el = MagicWeatherObject.GetCitiesData()[CityIndex];

  generate_default(el, MagicWeatherObject.Period, periodvec);

  auto renderer = ftxui::Renderer([&] {
    ListeningKeyBoardEvents(MagicWeatherObject, keys, periodvec, CityIndex, CitiesData_, el);
    return ftxui::vbox(ftxui::text(el.GetCityName()) | ftxui::center | ftxui::color(ftxui::Color::Blue), periodvec) | ftxui::yflex_shrink;
  }) ;

  renderer |= ftxui::CatchEvent([&](ftxui::Event e){
    keys.push_back(e);
    return true;
  });

  screen.Loop(renderer);
}
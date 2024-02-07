//
// Created by Святослав on 12.02.2024.
//

#include "Requests.h"

void City::GettingCoords() {
  std::string Ninjas_City_link = "https://api.api-ninjas.com/v1/city";
  std::string Token = "RBYjVh84e6mhv2V6R0SPQg==NNp47ySlItRaLCbf";
  cpr::Response Data = cpr::Get(cpr::Url{Ninjas_City_link}, cpr::Parameters{{"name", CityName}}, cpr::Header{{"X-Api-Key" , Token}});
  if (Data.status_code != 200){
    std::cerr << "This City was not Found by Ninjas-Api, use english and only current name of city.\n";
    exit(EXIT_FAILURE);
  }
  json Json_City = json::parse(Data.text);
//  std::cout << Json_City.dump(1) << "\n";
  CityName = Json_City[0]["name"];
  Longitude = Json_City[0]["longitude"];
  Latitude = Json_City[0]["latitude"];
  std::cout << Latitude << " " << Longitude << " " << CityName << " ";
}

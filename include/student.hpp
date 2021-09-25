// Copyright 2021 Daria <photodoshfy@gmail.com>

#ifndef INCLUDE_SOURCE_HPP_
#define INCLUDE_SOURCE_HPP_

#include <any>
#include <iostream>
#include <nlohmann/json.hpp>


using nlohmann::json;

struct student_t {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void from_json(const json& j, student_t& s);
auto get_name(const json& j) -> std::string;
auto get_debt(const json& j) -> std::any;
auto get_avg(const json& j) -> std::any;
auto get_group(const json& j) -> std::any;

#endif // INCLUDE_SOURCE_HPP_

#include <fstream>
#include <nlohmann/json.hpp>
#include <student.hpp>
#include <iostream>
void print(const student_t& student, std::ostream& os) {
  //...
  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "null";
  } else if (student.debt.type() == typeid(std::string)) {
    os << std::any_cast<std::string>(student.debt);
  } else {
    os
        << std::any_cast<std::vector<std::string> >(student.debt).size()
        << " items";
  }
}

void print(const std::vector<student_t>& students, std::ostream& os) {

  //...
  for (auto const& student : students) {
    print(student, os);
  }
}

int main() {
  std::string jsonPath= "/home/daria/CLionProjects/lab_01/students.json";
  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"unable to open json: " + jsonPath};
  }

  json data;
  file >> data;

  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student= item.get<student_t>();
    students.push_back(student);
  }
  //...
  //print(students, std::cout);
}

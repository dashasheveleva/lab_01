#include <fstream>
#include <nlohmann/json.hpp>
#include <student.hpp>
#include <iostream>
#include <iomanip>

using namespace std;

void print(const student_t& student, std::ostream& os) {

  //name
  os << "| " << setw(14) << left << std::string(student.name) << "| " ;

  //group
  if (student.group.type() == typeid(size_t)) {
    os << setw(7) << left << std::any_cast<size_t>(student.group) << "| " ;
  } else if (student.group.type() == typeid(std::string)) {
    os << setw(7) << left << std::any_cast<std::string>(student.group) << "| ";
  }

  //avg
  if (student.avg.type() == typeid(size_t)) {
    os << setw(5) << left << std::any_cast<size_t>(student.avg) << "| ";
  } else if (student.avg.type() == typeid(double)) {
    os << setw(5) << left << std::any_cast<double>(student.avg) << "| ";
  } else if (student.avg.type() == typeid(std::string)) {
    os << setw(5) << left << std::any_cast<std::string>(student.avg) << "| ";
  }

  //dept
  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << setw(14)<<left << "null" << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    os << setw(14)<<left << std::any_cast<std::string>(student.debt) << "|";
  } else if (student.debt.type() == typeid(std::vector<std::string>)) {
    os << setw(2) << std::any_cast<std::vector<std::string> >(student.debt).size()
       << "items" << "       |";
  }
  os << endl;
  os << "|---------------|--------|------|---------------|" << endl;
}

void print(const std::vector<student_t>& students, std::ostream& os) {

  //| name          | group  | avg  | debt          |
  //|---------------|--------|------|---------------|
  //| Ivanov Petr   | 1      | 4.25 | null          |
  //|---------------|--------|------|---------------|
  //| Sidorov Ivan  | 31     | 4.00 | C++           |
  //|---------------|--------|------|---------------|
  //| Pertov Nikita | IU8-31 | 3.33 | 3 items       |
  //|---------------|--------|------|---------------|

  os << "|" << setw(15)<<left << "name" << "|" << setw(8)<<left<< "group"
     << "|" << setw(6) <<left<< "avg" << "|" << setw(15)<<left<< "dept" << "|"
     << endl << "|---------------|--------|------|---------------|" << endl;

  for (auto const& student : students) {
    print(student, os);
  }
}

int main() {
  std::string jsonPath= "/home/daria/CLionProjects/lab_01/students.json";
  if (jsonPath.empty() == 0) {
    throw std::runtime_error{"No argument containing file path"};
  }
  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"Unable to open json: " + jsonPath};
  }

  json data;
  file >> data;

  std::vector<student_t> students;

  if (data["items"].size() == 0) {
    throw std::runtime_error{"No values in 'items'"};
  }
  if (data["_meta"]["count"].is_number() == 0) {
    throw std::runtime_error{"Value 'count' mast be of type integer"};
  }
  if (data["items"].size() != data["_meta"]["count"]) {
    throw std::runtime_error{"The value 'count' does not match the number of 'items'"};
  }

  for (auto const& item : data["items"]) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }

  print(students, cout);

}
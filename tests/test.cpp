// Copyright 2021 Daria <photodoshfy@gmail.com>
#include <gtest/gtest.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <student.hpp>
#include <iostream>
#include <typeinfo>

TEST(FilePathExist, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  bool var= jsonPath.empty();
  EXPECT_EQ(var, false);
}
TEST(FileExist, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  bool var= file.fail();
  EXPECT_EQ(var, false);
}
TEST(ItemsInArray, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  bool var= data["items"].size() > 0;
  EXPECT_EQ(var, true);
}
TEST(IsInteger, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  bool var= data["_meta"]["count"].is_number();
  EXPECT_EQ(var, true);
}
TEST(MetaCunt_LenItems, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data["items"]) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }
  size_t var1= data["_meta"]["count"];
  size_t var2= students.size();
  EXPECT_EQ(var1, var2);
}
TEST(GroupType, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data["items"]) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool var = false;
    if (student.group.type() == typeid(size_t)) {
      var = true;
    } else if (student.group.type() == typeid(std::string)) {
      var = true;
    }
    EXPECT_EQ(var, true);
  }
}
TEST(AvgType, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data["items"]) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool var = false;
    if (student.avg.type() == typeid(size_t)) {
      var = true;
    } else if (student.avg.type() == typeid(double)) {
      var= true;
    } else if (student.avg.type() == typeid(std::string)) {
      var = true;
    }
    EXPECT_EQ(var, true);
  }
}
TEST(DeptType, EmptyTest) {
  std::string jsonPath;
  jsonPath= JPATH;
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data["items"]) {
    student_t student;
    from_json(item, student);
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool var = false;
    if (student.debt.type() == typeid(std::nullptr_t)) {
      var = true;
    } else if (student.debt.type() == typeid(std::string)) {
      var = true;
    } else if (student.debt.type() == typeid(std::vector<std::string>)) {
      var = true;
    }
      EXPECT_EQ(var, true);
  }
}
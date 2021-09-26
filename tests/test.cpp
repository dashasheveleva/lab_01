// Copyright 2021 Daria <photodoshfy@gmail.com>
#include <gtest/gtest.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <student.hpp>
#include <iostream>

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
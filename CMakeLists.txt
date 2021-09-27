### Прописывается основная информация для сборки через CMake.
cmake_minimum_required(VERSION 3.12) # Минимальная версия CMake

set(CMAKE_CXX_STANDARD 17) # Стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательность установки
# указанного стандарта (если OFF (по умолчанию), то воспринимается как совет)

### Прописываются возможные опции сборки
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)


set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

### Если используется Hunter (пакетный менеджер)
include("cmake/HunterGate.cmake")
# Подключение CMake скрипта с дополнительными функциями
HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz" # URL к ядру Hunter
  SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a" # SHA1 хэш
)

### Название проекта
project(template VERSION 0.1.0)
### Дополнительные опции для компилятора (могут отсутствовать)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")  # Флаги для включения
# всех предупреждений и дропа компиляции при их наличии
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")
add_compile_definitions(JPATH="${CMAKE_CURRENT_SOURCE_DIR}/students.json")

### Подключение зависимых библиотек

hunter_add_package(GTest) # Указание Hunter о добавлении пакета GTest
find_package(GTest CONFIG REQUIRED) # Указание Hunter о добавлении пакета Boost с указанными компонентами

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

#### Библиотека
add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/student.cpp
)
#### Исполняемый файл
add_executable(demo
  ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/student.cpp
)
### Указание директорий с заголовочными файлами
target_include_directories(
        ${PROJECT_NAME} # Цель, при сборке которой учитываются указанные пути к заголовочным файлам
        PUBLIC # область видимости
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
### Указание библиотек для линковки
target_link_libraries(
        demo # Цель, к которой просходит линковка
        ${PROJECT_NAME})  # Библиотеки, которые линкуются к цели

if(BUILD_TESTS)
  add_executable(tests
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
  )
  target_link_libraries(tests ${CMAKE_CURRENT_SOURCE_DIR} GTest::gtest_main)
  target_link_libraries(tests ${PROJECT_NAME})
  ## Тестирование
  enable_testing() # Включение тестирования
  add_test(NAME unit_tests COMMAND tests) # При тестировании выполнится исполняемый файл tests
endif()

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage/cmake")
  find_package(codecov)
  string(APPEND CMAKE_CXX_FLAGS " --coverage")
  add_coverage(${PROJECT_NAME})
  add_coverage(tests)
  coverage_evaluate()
endif()

if(BUILD_DOCS)
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/_docs)
  set(DOXYGEN_EXAMPLE_PATH examples)
  set(DOXYGEN_GENERATE_HTML NO)
  set(DOXYGEN_GENERATE_MAN YES)
  find_package(Doxygen)
  doxygen_add_docs(docs include)
  install(DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY}/man DESTINATION share)
  # add_dependencies(install docs) need to call target docs before install or package
endif()

include(CPackConfig.cmake)

install(TARGETS ${PROJECT_NAME} demo
  EXPORT "${PROJECT_NAME}-targets"
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(EXPORT "${PROJECT_NAME}-targets"
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION "lib/cmake"
)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)



project(${CMAKE_PROJECT_NAME})

find_package(oatpp REQUIRED)

add_executable(app App.cpp)

target_link_libraries(app PRIVATE oatpp::oatpp)

target_include_directories(app
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})

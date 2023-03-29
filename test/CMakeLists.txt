project(${CMAKE_PROJECT_NAME})

find_package(oatpp REQUIRED)

add_executable(test Test.cpp MyControllerTest.cpp)

target_link_libraries(test PRIVATE oatpp::oatpp-test)

target_include_directories(test
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src/)

enable_testing()
add_test(test_all test)

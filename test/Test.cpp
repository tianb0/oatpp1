#include "MyControllerTest.hpp"

#include <iostream>
#include <oatpp-test/UnitTest.hpp>
#include <oatpp/core/base/Environment.hpp>

void runTests() {
  OATPP_RUN_TEST(MyControllerTest);

  // TODO: add more tests below
}

int main() {
  oatpp::base::Environment::init();

  runTests();

  // print how much objects were created during app running, and what have left-probably leaked
  // disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better perfromance
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);
  
  oatpp::base::Environment::destroy();

  return 0;
}

#include "MyControllerTest.hpp"

#include "controller/MyController.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"
#include "dto/DTOs.hpp"

#include <chrono>
#include <memory>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/web/client/HttpRequestExecutor.hpp>

#include <oatpp-test/web/ClientServerTestRunner.hpp>
#include <thread>

void MyControllerTest::onRun() {
  // register test components
  TestComponent component;

  // craete client-server test runner
  oatpp::test::web::ClientServerTestRunner runner;

  // add MyController endpoints to the router of the test server
  runner.addController(std::make_shared<MyController>());

  // run tests
  runner.run([this, &runner] {
    // get client connection provider for api client
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
    
    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
    auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);
    auto response = client->getHello();

    OATPP_ASSERT(response->getStatusCode() == 200);
    
    auto message = response->readBodyToDto<oatpp::Object<MessageDto>>(objectMapper.get());

    OATPP_ASSERT(message);
    OATPP_ASSERT(message->statusCode == 200);
    OATPP_ASSERT(message->message == "hello world");
  }, std::chrono::minutes(10)); // test timeout

  // wait all server threads finished
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

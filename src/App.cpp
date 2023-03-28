#include "controller/MyController.hpp"
#include "AppComponent.hpp"

#include <memory>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/network/ConnectionHandler.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

void run() {
  // register components in scope of run() method
  AppComponent components;

  // get router component
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  // create MyController and add all of its endpoints to router
  auto myController = std::make_shared<MyController>();
  router->addController(myController);

  // get connection handler component
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  // get connection provider component
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  // create server which tasks provided tcp connections and passes them to http connection handler
  oatpp::network::Server server(connectionProvider, connectionHandler);

  // print info about server port
  OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

  server.run();
}

int main() {
  // init oatapp env
  oatpp::base::Environment::init();

  run();

  // destroy oatpp env
  oatpp::base::Environment::destroy();

  return 0;
}

#ifndef AppComponent_hpp
#define AppComponent_hpp

#include <memory>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/ConnectionHandler.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>

#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

// class which creates and holds application components and registers components
// in oatpp::base::Environment
// order of components initialization is from top to bottom

class AppComponent {
public:
  // create connection provider component which listens on the port
  OATPP_CREATE_COMPONENT(
      std::shared_ptr<oatpp::network::ServerConnectionProvider>,
      serverConnectionProvider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"localhost", 8000, oatpp::network::Address::IP_4});
  }());

  // create router component
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                         httpRouter)
  ([] { return oatpp::web::server::HttpRouter::createShared(); }());

  // create connection handler component
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                         serverConnectionHandler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                    router); // get router component
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());

  // create object mapper to  serialize/deserialize dtos in controller's api
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                         apiObjectMapper)
  ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());
};

#endif

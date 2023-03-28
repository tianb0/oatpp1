#ifndef DTOs_hpp
#define DTOs_hpp

#include <oatpp/core/Types.hpp>
#include <oatpp/core/data/mapping/type/Object.hpp>
#include <oatpp/core/macro/codegen.hpp>

// begin DTO code generation
#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO {

  DTO_INIT(MessageDto, DTO /* extends */)

  DTO_FIELD(Int32, statusCode); // status code field
  DTO_FIELD(String, message); // message field
};


// TODO: add more DTOs below

// end DTO code generation
#include OATPP_CODEGEN_END(DTO)


#endif

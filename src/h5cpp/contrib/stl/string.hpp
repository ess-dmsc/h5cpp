#pragma once

#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/datatype/string.hpp>
#include <string>

namespace hdf5 { 
namespace datatype { 

template<>
class TypeTrait<std::string> {
 public:
  using Type = std::string;
  using TypeClass = String;
  static TypeClass create(const Type & = Type()) {
    return datatype::String::variable();
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};


template<typename CharT>
class TypeTrait<std::basic_string<CharT>> {
 private:

 public:
  using Type = std::basic_string<CharT>;
  using TypeClass = String;

  static TypeClass create(const Type & = Type()) {
    static_assert(std::is_same<CharT, char>::value, "Only support 8Bit characters");

    String type = String::variable();
    type.encoding(CharacterEncoding::UTF8);
    return type;

  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }

};
} // end of namespace datatype

namespace dataspace { 

} // end of namespace dataspace
} // end of namespace hdf5

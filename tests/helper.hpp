#pragma once

#include FS_HEADER

#include <iostream>
#include <fstream>

#include <tao/json/value.hpp>
#include <tao/json/from_stream.hpp>

namespace fs = FS_NAMESPACE;

namespace arangodb::validation {
    [[nodiscard]] tao::json::value parse_tao_value_from_stream(fs::path const & name ) {
      std::ifstream ifs(name);
      return tao::json::from_stream(ifs, name, 192 /*max buffer*/);
    }
}

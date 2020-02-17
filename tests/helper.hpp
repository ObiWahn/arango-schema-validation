#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>

#include <tao/json/value.hpp>
#include <tao/json/from_stream.hpp>

namespace arangodb::validation {
    [[nodiscard]] tao::json::value parse_tao_value_from_stream( const std::filesystem::path& name ) {
      std::ifstream ifs(name);
      return tao::json::from_stream(ifs, name, 192 /*max buffer*/);
    }
}

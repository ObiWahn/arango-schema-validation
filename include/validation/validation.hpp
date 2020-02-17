#pragma once

#include <velocypack/Slice.h>
#include <velocypack/velocypack-aliases.h>

#include <tao/json/contrib/schema.hpp>
#include <tao/json/value.hpp>


namespace arangodb::validation {
bool validate(tao::json::value const& doc, tao::json::schema const& schema); // first step
bool validate(VPackSlice const doc, tao::json::schema const& schema);        // final
} // namespace arangodb::validation

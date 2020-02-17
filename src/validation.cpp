#include <validation/validation.hpp>

namespace arangodb::validation {
bool validate(VPackSlice const, tao::json::schema const&) {
    // TODO
    // option1: convert slice ot tao::value (we need this schema creations anyway)
    // option2: implement validation on slice - more work (only if conversion is too slow)
    throw std::runtime_error("not implemented");
}

bool validate(tao::json::value const& doc, tao::json::schema const& schema) {
    return schema.validate(doc);
}
} // namespace arangodb::validation

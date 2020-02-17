#include <gtest/gtest.h>

#include "helper.hpp"
#include <validation/validation.hpp>

namespace {
fs::path const test_dir = fs::path{ARANGO_VALIDATION_TEST_DIR} / "test_data";
}

TEST(small_sample, schema_1) {
    auto file = test_dir / "schema_1.json";
    auto tao_value = arangodb::validation::parse_tao_value_from_stream(file);
    tao::json::schema schema(tao_value.at("schema"));
    auto doc = tao_value.at("doc");
    bool result = arangodb::validation::validate(doc, schema);
    std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << std::boolalpha << result << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
}

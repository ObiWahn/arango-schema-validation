#include <gtest/gtest.h>

#include "helper.hpp"
#include <tao/json/contrib/schema.hpp>
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
}

TEST(small_sample, slice_to_value_success) {
    VPackBuilder builder;
    {
        VPackObjectBuilder o(&builder);
        builder.add(VPackValue("schema"));
        {
            VPackObjectBuilder sub(&builder);
            builder.add("type", VPackValue("array"));
            builder.add(VPackValue("items"));
            {
                VPackObjectBuilder subsub(&builder);
                builder.add("type", VPackValue("number"));
                builder.add("maximum", VPackValue(6));
            }
        }
        builder.add(VPackValue("doc"));
        {
            VPackArrayBuilder sub(&builder);
            builder.add(VPackValue(1));
            builder.add(VPackValue(2));
            builder.add(VPackValue(3));
            builder.add(VPackValue(4));
        };
    }

    auto tao_value = arangodb::validation::slice_to_value(builder.slice());
    tao::json::schema schema(tao_value.at("schema"));
    auto doc = tao_value.at("doc");
    bool result = arangodb::validation::validate(doc, schema);
    ASSERT_TRUE(result);
}

TEST(small_sample, slices_to_value_fail) {
    VPackBuilder builder;
    {
        VPackObjectBuilder o(&builder);
        builder.add(VPackValue("schema"));
        {
            VPackObjectBuilder sub(&builder);
            builder.add("type", VPackValue("array"));
            builder.add(VPackValue("items"));
            {
                VPackObjectBuilder subsub(&builder);
                builder.add("type", VPackValue("number"));
                builder.add("maximum", VPackValue(6));
            }
        }
        builder.add(VPackValue("doc"));
        {
            VPackArrayBuilder sub(&builder);
            builder.add(VPackValue(1));
            builder.add(VPackValue(2));
            builder.add(VPackValue(3));
            builder.add(VPackValue(4));
            builder.add(VPackValue(8));
        };
    }

    auto tao_value = arangodb::validation::slice_to_value(builder.slice());
    tao::json::schema schema(tao_value.at("schema"));
    auto doc = tao_value.at("doc");
    bool result = arangodb::validation::validate(doc, schema);
    ASSERT_FALSE(result);
}

TEST(small_sample, events_from_slice_success) {
    VPackBuilder builder;
    {
        VPackObjectBuilder o(&builder);
        builder.add(VPackValue("schema"));
        {
            VPackObjectBuilder sub(&builder);
            builder.add("type", VPackValue("array"));
            builder.add(VPackValue("items"));
            {
                VPackObjectBuilder subsub(&builder);
                builder.add("type", VPackValue("number"));
                builder.add("maximum", VPackValue(6));
            }
        }
        builder.add(VPackValue("doc"));
        {
            VPackArrayBuilder sub(&builder);
            builder.add(VPackValue(1));
            builder.add(VPackValue(2));
            builder.add(VPackValue(3));
            builder.add(VPackValue(4));
        };
    }

    auto tao_value = arangodb::validation::slice_to_value(builder.slice());
    tao::json::schema schema(tao_value.at("schema"));
    bool result = arangodb::validation::validate(builder.slice().get("doc"), &VPackOptions::Defaults, schema);
    ASSERT_TRUE(result);
}

TEST(small_sample, events_from_slice_fail) {
    VPackBuilder builder;
    {
        VPackObjectBuilder o(&builder);
        builder.add(VPackValue("schema"));
        {
            VPackObjectBuilder sub(&builder);
            builder.add("type", VPackValue("array"));
            builder.add(VPackValue("items"));
            {
                VPackObjectBuilder subsub(&builder);
                builder.add("type", VPackValue("number"));
                builder.add("maximum", VPackValue(6));
            }
        }
        builder.add(VPackValue("doc"));
        {
            VPackArrayBuilder sub(&builder);
            builder.add(VPackValue(1));
            builder.add(VPackValue(2));
            builder.add(VPackValue(3));
            builder.add(VPackValue(4));
            builder.add(VPackValue(7));
        };
    }

    auto tao_value = arangodb::validation::slice_to_value(builder.slice());
    tao::json::schema schema(tao_value.at("schema"));
    bool result = arangodb::validation::validate(builder.slice().get("doc"), &VPackOptions::Defaults, schema);
    ASSERT_FALSE(result);
}

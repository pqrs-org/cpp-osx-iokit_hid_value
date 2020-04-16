#include <catch2/catch.hpp>

#include <pqrs/osx/iokit_hid_value/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json") {
  {
    pqrs::osx::iokit_hid_value hid_value1(pqrs::osx::chrono::absolute_time_point(1234),
                                          1,
                                          pqrs::hid::usage_page::value_t(5678),
                                          pqrs::hid::usage::value_t(4321));

    nlohmann::json actual = hid_value1;
    auto expected = nlohmann::json::object(
        {
            {"time_stamp", 1234},
            {"integer_value", 1},
            {"usage_page", 5678},
            {"usage", 4321},
        });
    REQUIRE(actual == expected);

    auto hid_value2 = actual.get<pqrs::osx::iokit_hid_value>();
    REQUIRE(hid_value1 == hid_value2);
  }

  {
    auto json = nlohmann::json::object();
    auto hid_value = json.get<pqrs::osx::iokit_hid_value>();
    REQUIRE(hid_value.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(0));
    REQUIRE(hid_value.get_integer_value() == 0);
    REQUIRE(hid_value.get_usage_page() == std::nullopt);
    REQUIRE(hid_value.get_usage() == std::nullopt);
  }

  REQUIRE_THROWS_AS(
      nlohmann::json::array().get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::array().get<pqrs::osx::iokit_hid_value>(),
      "json must be object, but is `[]`");

  REQUIRE_THROWS_AS(
      nlohmann::json::object({{"time_stamp", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::object({{"time_stamp", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      "`time_stamp` must be number, but is `null`");

  REQUIRE_THROWS_AS(
      nlohmann::json::object({{"integer_value", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::object({{"integer_value", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      "`integer_value` must be number, but is `null`");

  REQUIRE_THROWS_AS(
      nlohmann::json::object({{"usage_page", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::object({{"usage_page", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      "`usage_page` must be number, but is `null`");

  REQUIRE_THROWS_AS(
      nlohmann::json::object({{"usage", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::object({{"usage", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      "`usage` must be number, but is `null`");

  REQUIRE_THROWS_AS(
      nlohmann::json::object({{"Usage", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      pqrs::json::unmarshal_error);
  REQUIRE_THROWS_WITH(
      nlohmann::json::object({{"Usage", nullptr}}).get<pqrs::osx::iokit_hid_value>(),
      "unknown key: `Usage`");
}

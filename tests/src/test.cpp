#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/osx/iokit_hid_value.hpp>

TEST_CASE("iokit_hid_value") {
  pqrs::osx::iokit_hid_value hid_value1(pqrs::osx::chrono::absolute_time_point(1234),
                                        1,
                                        pqrs::osx::iokit_hid_usage_page::value_t(5678),
                                        pqrs::osx::iokit_hid_usage::value_t(4321));

  REQUIRE(hid_value1.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(1234));
  REQUIRE(hid_value1.get_integer_value() == 1);
  REQUIRE(hid_value1.get_usage_page() == pqrs::osx::iokit_hid_usage_page::value_t(5678));
  REQUIRE(hid_value1.get_usage() == pqrs::osx::iokit_hid_usage::value_t(4321));

  REQUIRE(hid_value1.conforms_to(pqrs::osx::iokit_hid_usage_page::value_t(5678), pqrs::osx::iokit_hid_usage::value_t(4321)) == true);
  REQUIRE(hid_value1.conforms_to(pqrs::osx::iokit_hid_usage_page::value_t(5679), pqrs::osx::iokit_hid_usage::value_t(4321)) == false);
  REQUIRE(hid_value1.conforms_to(pqrs::osx::iokit_hid_usage_page::value_t(5678), pqrs::osx::iokit_hid_usage::value_t(4320)) == false);

  auto hid_value2 = hid_value1;
  REQUIRE(hid_value1 == hid_value2);

  hid_value2 = hid_value1;
  hid_value2.set_time_stamp(pqrs::osx::chrono::absolute_time_point(1235));
  REQUIRE(hid_value1 != hid_value2);

  hid_value2 = hid_value1;
  hid_value2.set_integer_value(0);
  REQUIRE(hid_value1 != hid_value2);

  hid_value2 = hid_value1;
  hid_value2.set_usage_page(pqrs::osx::iokit_hid_usage_page::value_t(5679));
  REQUIRE(hid_value1 != hid_value2);

  hid_value2 = hid_value1;
  hid_value2.set_usage(pqrs::osx::iokit_hid_usage::value_t(4320));
  REQUIRE(hid_value1 != hid_value2);
}

TEST_CASE("iokit_hid_value nullptr") {
  pqrs::osx::iokit_hid_value hid_value(nullptr);
  REQUIRE(hid_value.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(0));
  REQUIRE(hid_value.get_integer_value() == 0);
  REQUIRE(hid_value.get_usage_page() == std::nullopt);
  REQUIRE(hid_value.get_usage() == std::nullopt);
}

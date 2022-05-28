#include "nlohmann_json_test.hpp"
#include <boost/ut.hpp>
#include <pqrs/osx/iokit_hid_value.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "iokit_hid_value"_test = [] {
    pqrs::osx::iokit_hid_value hid_value1(pqrs::osx::chrono::absolute_time_point(1234),
                                          1,
                                          pqrs::hid::usage_page::value_t(5678),
                                          pqrs::hid::usage::value_t(4321));

    expect(hid_value1.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(1234));
    expect(hid_value1.get_integer_value() == 1);
    expect(hid_value1.get_usage_page() == pqrs::hid::usage_page::value_t(5678));
    expect(hid_value1.get_usage() == pqrs::hid::usage::value_t(4321));

    expect(hid_value1.conforms_to(pqrs::hid::usage_page::value_t(5678), pqrs::hid::usage::value_t(4321)) == true);
    expect(hid_value1.conforms_to(pqrs::hid::usage_page::value_t(5679), pqrs::hid::usage::value_t(4321)) == false);
    expect(hid_value1.conforms_to(pqrs::hid::usage_page::value_t(5678), pqrs::hid::usage::value_t(4320)) == false);

    auto hid_value2 = hid_value1;
    expect(hid_value1 == hid_value2);

    hid_value2 = hid_value1;
    hid_value2.set_time_stamp(pqrs::osx::chrono::absolute_time_point(1235));
    expect(hid_value1 != hid_value2);

    hid_value2 = hid_value1;
    hid_value2.set_integer_value(0);
    expect(hid_value1 != hid_value2);

    hid_value2 = hid_value1;
    hid_value2.set_usage_page(pqrs::hid::usage_page::value_t(5679));
    expect(hid_value1 != hid_value2);

    hid_value2 = hid_value1;
    hid_value2.set_usage(pqrs::hid::usage::value_t(4320));
    expect(hid_value1 != hid_value2);
  };

  "iokit_hid_value nullptr"_test = [] {
    pqrs::osx::iokit_hid_value hid_value(nullptr);
    expect(hid_value.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(0));
    expect(hid_value.get_integer_value() == 0);
    expect(hid_value.get_usage_page() == std::nullopt);
    expect(hid_value.get_usage() == std::nullopt);
  };

  run_nlohmann_json_test();

  return 0;
}

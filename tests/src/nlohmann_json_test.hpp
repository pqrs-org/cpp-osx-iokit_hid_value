#include <boost/ut.hpp>
#include <pqrs/osx/iokit_hid_value/extra/nlohmann_json.hpp>

void run_nlohmann_json_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "nlohmann_json"_test = [] {
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
      expect(actual == expected);

      auto hid_value2 = actual.get<pqrs::osx::iokit_hid_value>();
      expect(hid_value1 == hid_value2);
    }

    {
      auto json = nlohmann::json::object();
      auto hid_value = json.get<pqrs::osx::iokit_hid_value>();
      expect(hid_value.get_time_stamp() == pqrs::osx::chrono::absolute_time_point(0));
      expect(hid_value.get_integer_value() == 0);
      expect(hid_value.get_usage_page() == std::nullopt);
      expect(hid_value.get_usage() == std::nullopt);
    }

    try {
      nlohmann::json::array().get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("json must be object, but is `[]`") == ex.what());
    } catch (...) {
      expect(false);
    }

    try {
      nlohmann::json::object({{"time_stamp", nullptr}}).get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`time_stamp` must be number, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    try {
      nlohmann::json::object({{"integer_value", nullptr}}).get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`integer_value` must be number, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    try {
      nlohmann::json::object({{"usage_page", nullptr}}).get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`usage_page` must be number, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    try {
      nlohmann::json::object({{"usage", nullptr}}).get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`usage` must be number, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    try {
      nlohmann::json::object({{"Usage", nullptr}}).get<pqrs::osx::iokit_hid_value>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("unknown key: `Usage`") == ex.what());
    } catch (...) {
      expect(false);
    }
  };
}

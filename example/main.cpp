#include <pqrs/osx/iokit_hid_value.hpp>

int main(void) {
  pqrs::osx::iokit_hid_value hid_value(pqrs::osx::chrono::absolute_time_point(1000),
                                       1,
                                       pqrs::osx::iokit_hid_usage_page_keyboard_or_keypad,
                                       pqrs::osx::iokit_hid_usage(0x04));

  std::cout << "time_stamp:" << hid_value.get_time_stamp() << std::endl;

  return 0;
}

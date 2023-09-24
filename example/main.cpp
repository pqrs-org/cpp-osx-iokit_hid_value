#include <pqrs/osx/iokit_hid_value.hpp>

int main(void) {
  pqrs::osx::iokit_hid_value hid_value(pqrs::osx::chrono::absolute_time_point(1000),
                                       1,
                                       pqrs::hid::usage_page::keyboard_or_keypad,
                                       pqrs::hid::usage::keyboard_or_keypad::keyboard_a,
                                       1,
                                       0);

  std::cout << "time_stamp:" << hid_value.get_time_stamp() << std::endl;

  return 0;
}

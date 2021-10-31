#include "plugin.h"

namespace CTRPluginFramework::ACNL {
  GameKbd* GameKbd::get_instance() {
    if (!read_from<u32>(0x958114))
      return nullptr;

    return (GameKbd*)read_from<u32>(0x958108);
  }

  u32& GameKbd::length() {
    return read_from<u32>(read_from<u32>(0x958114) + 8);
  }

  void GameKbd::clear() {
    memset(buffer, 0, sizeof(buffer));
    length() = 0;
  }

  void GameKbd::set(std::u16string const& str) {
    memcpy(buffer, str.c_str(), str.length() * sizeof(char16_t));
    length() = str.length();
  }

  std::u16string_view GameKbd::get() {
    return std::u16string_view(buffer, length());
  }

  void GameKbd::push_back(char16_t ch) {
    if (length() >= 32)
      return;

    buffer[length()] = ch;
    length()++;
  }

  void GameKbd::push_back(std::u16string const& str) {
    for (auto&& ch : str)
      push_back(ch);
  }

  void GameKbd::pop_back() {
    if (length() >= 1)
      length()--;
  }

  void GameKbd::send() {
    read_from<u8>(0x9580E1) = 1;
  }
} // namespace CTRPluginFramework::ACNL
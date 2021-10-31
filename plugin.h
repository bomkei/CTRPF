#pragma once

#define NORETURN __attribute__((noreturn))
#define U64_MAX UINT64_MAX

#ifndef SSIZE_MAX
#ifdef SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

#include <string>
#include <string_view>
#include <vector>
#include <tuple>
#include <CTRPluginFramework.hpp>

#define ADDR_DROP_ITEM 0x59E5B4
#define ADDR_DROP_CHECK 0x5979E4

template <class T>
T& write_to(u32 addr, T const& val) {
  return *(T*)(addr) = val;
}

template <class T>
T& read_from(u32 addr) {
  return *(T*)(addr);
}

template <u32 addr, class... Args>
u32 call_addr(Args&&... args) {
  return ((u32(*)(Args...))(addr))(args...);
}

template <class T>
T& switching(T& x, T const& a, T const& b) {
  if (x == a)
    return x = b;

  return x = a;
}

namespace CTRPluginFramework::ACNL {
  struct Coordinates {
    float x, y, z;
  };

  struct GameKbd {
    char16_t buffer[32];

    GameKbd()               = delete;
    GameKbd(GameKbd&&)      = delete;
    GameKbd(GameKbd const&) = delete;
    ~GameKbd()              = delete;

    static GameKbd* get_instance();

    u32& length();

    void clear();

    void set(std::u16string const& str);
    std::u16string_view get();

    void push_back(char16_t ch);
    void push_back(std::u16string const& str);
    void pop_back();

    void send();
  };

  struct Dropper {
    bool drop_check(u32& wx, u32& wy);

    // looks like dropped from inventory
    bool drop_item(u32 item);

    // drop to specified position on map
    bool drop_item_to_position(u32 item, u32 x, u32 y);
  };

  void select_player(u8 index);
  u8 get_selected_player();

} // namespace CTRPluginFramework::ACNL

namespace CTRPluginFramework {
  int FlagKeyboard(
    std::string const& msg, std::vector<std::tuple<char const*, bool&>>& items);

  class KeyboardJPImpl;
  class KeyboardJP {
  public:
    KeyboardJP(std::string const& text = "");
    ~KeyboardJP();

    void SetMaxLength(u32 max) const;
    // void CanSwitch(bool canSwitch) const;
    // void CanAbort(bool canAbort) const;
    int Open(std::string& out);

  private:
    std::unique_ptr<KeyboardJPImpl> _impl;
  };

  namespace ScreenTester {
    void screen_test(MenuEntry*);
    void screen_test_menufunc(MenuEntry*);
  } // namespace ScreenTester

  void jpn_keyboard(MenuEntry*);
} // namespace CTRPluginFramework
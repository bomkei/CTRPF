#include <locale>
#include <codecvt>
#include "plugin.h"

namespace CTRPluginFramework {
  class KeyboardJPImpl {
    friend class KeyboardJP;

    u32 max_length;
    bool can_switch;
    bool can_abort;

    std::u16string data;

    KeyboardJPImpl(std::string const& text)
        : max_length(0)
        , can_switch(false)
        , can_abort(false) {
      data = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>()
               .from_bytes(text);
    }

    void Draw(Screen const& scr) {
      scr.DrawRect(20, 20, 280, 200, Color::Black);
      scr.DrawRect(22, 22, 276, 196, Color::White, 0);
    }

    int Open() {
    }

  public:
    ~KeyboardJPImpl() = default;
  };

  KeyboardJP::KeyboardJP(std::string const& text) {
  }

  KeyboardJP::~KeyboardJP() {
  }

  void KeyboardJP::SetMaxLength(u32 max) const {
    _impl->max_length = max;
  }

  int KeyboardJP::Open(std::string& out) {
    return _impl->Open();
  }
} // namespace CTRPluginFramework
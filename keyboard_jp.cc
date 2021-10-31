#include <locale>
#include <codecvt>
#include "plugin.h"

namespace CTRPluginFramework {
  static wchar_t const* keymap = L"”わらやまはなたさかあ←"
                                 L"゜をりゆみひにちしきい↓"
                                 L"小んるよむふぬつすくう "
                                 L"あ、れ！めへねてせけえー"
                                 L"ア。ろ？もほのとそこお空";

  static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;

  constexpr auto posX = 40;
  constexpr auto posY = 68;

  constexpr auto keyWidth  = 20;
  constexpr auto keyHeight = 18;

  constexpr auto panelWidth  = 12;
  constexpr auto panelHeight = 5;

  class KeyboardJPImpl {
    friend class KeyboardJP;

    u32 max_length;
    bool can_switch;
    bool can_abort;

    UIntVector tch_pos;
    bool is_touch = 0;
    int cursor_x  = 0;

    std::u16string data;

    KeyboardJPImpl(std::string const& text)
        : max_length(0)
        , can_switch(false)
        , can_abort(false) {
      data = conv.from_bytes(text);
    }

    void Draw(Screen const& scr) {
      static u8 cursor_tick  = 0;
      static u8 cursor_tick2 = 0;

      scr.DrawRect(20, 20, 280, 200, Color::Black);
      scr.DrawRect(22, 22, 276, 196, Color::White, 0);

      scr.DrawSysfont(conv.to_bytes(data), posX, 32);
      scr.DrawRect(48);

      if (cursor_tick & 1) {
        scr.DrawRect(posX, 32, 1, 16, Color::White);
      }

      for (int x = 0; x < panelWidth; x++) {
        for (int y = 0; y < panelHeight; y++) {
          auto p = keymap + x + y * panelWidth;

          if (is_touch && tch_pos.x == x && tch_pos.y == y) {
            scr.DrawRect(
              posX + x * keyWidth, posY + y * keyHeight, keyWidth, keyHeight,
              Color::Gray);
          }

          scr.DrawSysfont(
            conv.to_bytes(std::u16string(1, *p)), posX + x * keyWidth,
            posY + y * keyHeight);
        }
      }

      cursor_tick2++;

      if (cursor_tick2 >= 30) {
        cursor_tick++;
        cursor_tick2 = 0;
      }
    }

    void Control() {
      is_touch = Touch::IsDown();
      tch_pos  = Touch::GetPosition();

      if (is_touch) {
        tch_pos.x /= keyWidth;
        tch_pos.y /= keyHeight;

        auto p = keymap + tch_pos.x + tch_pos.y * panelWidth;

        data.push_back((wchar_t)*p);
      }
    }

    int Open() {
      auto paused = Process::IsPaused();

      if (!paused)
        Process::Pause();

      auto const& scr = OSD::GetBottomScreen();

      while (1) {
        Controller::Update();

        Control();
        Draw(scr);

        OSD::SwapBuffers();
      }

      if (!paused)
        Process::Play();

      return 0;
    }

  public:
    ~KeyboardJPImpl() = default;
  };

  KeyboardJP::KeyboardJP(std::string const& text)
      : _impl(new KeyboardJPImpl(text)) {
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
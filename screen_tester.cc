#include "plugin.h"

namespace CTRPluginFramework {
  namespace ScreenTester {
    namespace {
      bool use_top = true;

      int pos_x = 0;
      int pos_y = 0;

      bool ctrl_abxy  = false;
      bool ctrl_dpad  = true;
      bool ctrl_stick = false;
      bool ctrl_touch = false;

      constexpr auto cursor_size = 16;

      std::vector<std::tuple<char const*, bool&>> opt_flags{
        {"Use TopScreen", use_top}, {"ABXY", ctrl_abxy},   {"D-Pad", ctrl_dpad},
        {"Stick", ctrl_stick},      {"Touch", ctrl_touch},
      };
    } // namespace

    bool screen_test_osdcb(Screen const& screen) {
      if (screen.IsTop != use_top)
        return false;

      // position
      screen.Draw(Utils::Format("X=%d, Y=%d", pos_x, pos_y), 0, 0);

      // cursor
      {
        auto const& C = Color::Red;

        screen.DrawRect(pos_x, pos_y, 2, 2, C);

        // left to center
        screen.DrawRect(pos_x - cursor_size / 2, pos_y, cursor_size / 2, 2, C);

        // top to center
        screen.DrawRect(pos_x, pos_y - cursor_size / 2, 2, cursor_size / 2, C);

        // right to center
        screen.DrawRect(pos_x, pos_y, cursor_size / 2, 2, C);

        // bottom to center
        screen.DrawRect(pos_x, pos_y, 2, cursor_size / 2, C);
      }

      return true;
    }

    void screen_test(MenuEntry* entry) {
      if (entry->WasJustActivated())
        OSD::Run(screen_test_osdcb);
      else if (!entry->IsActivated())
        OSD::Stop(screen_test_osdcb);

      u32 keys = Controller::GetKeysDown();

      if (ctrl_dpad) {
        if (keys & Key::DPadUp)
          pos_y--;
        if (keys & Key::DPadDown)
          pos_y++;
        if (keys & Key::DPadLeft)
          pos_x--;
        if (keys & Key::DPadRight)
          pos_x++;
      }

      if (ctrl_stick) {
        if (keys & Key::CPadUp)
          pos_y--;
        if (keys & Key::CPadDown)
          pos_y++;
        if (keys & Key::CPadLeft)
          pos_x--;
        if (keys & Key::CPadRight)
          pos_x++;
      }

      if (ctrl_touch && keys & Key::Touchpad) {
        auto const& pos = Touch::GetPosition();

        pos_x = pos.x;
        pos_y = pos.y;
      }

      if (pos_x < 0)
        pos_x = 0;
      if (pos_y < 0)
        pos_y = 0;
      if (pos_y >= 240)
        pos_y = 239;
      if (pos_x >= 400)
        pos_x = 399;
    }

    void screen_test_menufunc(MenuEntry* entry) {
      FlagKeyboard("", opt_flags);
    }
  } // namespace ScreenTester
} // namespace CTRPluginFramework
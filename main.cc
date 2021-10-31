#include "plugin.h"

namespace CTRPluginFramework {
  void jpn_keyboard(MenuEntry*) {
    std::string str;

    KeyboardJP().Open(str);
  }
} // namespace CTRPluginFramework

namespace CTRPluginFramework {
  void init_menu(PluginMenu& menu) {
    menu.SynchronizeWithFrame(true);

    menu += new MenuFolder(
      "utils", {new MenuEntry(
                 "screen test", ScreenTester::screen_test,
                 ScreenTester::screen_test_menufunc)});

    menu += new MenuEntry("jpn keyboard", nullptr, jpn_keyboard);
  }

  int main() {
    PluginMenu menu{"ACNL Plugin"};

    init_menu(menu);

    return menu.Run();
  }
} // namespace CTRPluginFramework
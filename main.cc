#include "plugin.h"

namespace CTRPluginFramework {
  void init_menu(PluginMenu& menu) {
    menu.SynchronizeWithFrame(true);

    menu += new MenuFolder(
      "utils", {new MenuEntry(
                 "screen test", ScreenTester::screen_test,
                 ScreenTester::screen_test_menufunc)});
  }

  int main() {
    PluginMenu menu{"ACNL Plugin"};

    init_menu(menu);

    return menu.Run();
  }
} // namespace CTRPluginFramework
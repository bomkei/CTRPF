#include "plugin.h"

namespace CTRPluginFramework::ACNL {
  static u8 g_selected_player = 4;

  void select_player(u8 index) {
    g_selected_player = index;
  }

  u8 get_selected_player() {
    return g_selected_player;
  }
} // namespace CTRPluginFramework::ACNL
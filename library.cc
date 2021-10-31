#include "plugin.h"

namespace CTRPluginFramework {
  int FlagKeyboard(
    std::string const& msg,
    std::vector<std::tuple<char const*, bool&>>& items) {

    std::vector<std::string> opt;

    for (auto&& i : items) {
      opt.emplace_back(
        Utils::Format("[%c] %s", std::get<1>(i) ? '*' : ' ', std::get<0>(i)));
    }

    while (1) {
      auto r = Keyboard(msg, opt).Open();

      if (r < 0)
        return r;

      std::get<1>(items[r]) ^= 1;
      switching(opt[r][1], '*', ' ');
    }

    return 0;
  }
} // namespace CTRPluginFramework
#include "plugin.h"

namespace CTRPluginFramework::ACNL {
  bool Dropper::drop_check(u32& wx, u32& wy) {
    u32 u0;
    return call_addr<ADDR_DROP_CHECK>(&wx, &wy, &u0, 0, 0);
  }

  /*

        u32 Dropper::PlaceItem(u8 ID, u32 *ItemToReplace, u32 *ItemToPlace, u32
     *ItemToShow, u8 worldx, u8 worldy, bool u0, bool u1, bool u2, bool u3, bool
     u4) { return Code::PlaceItemOffset.Call<u32>(ID, (u32)ItemToReplace,
     (u32)ItemToPlace, (u32)ItemToShow, worldx, worldy, u0, u1, u2, u3, u4);
        }

                                Dropper::PlaceItemWrapper(DropType,
     ItemIDToReplace, &dropitem, &dropitem, wX, wY, 0, 0, 0, 0, 0, waitAnim,
     0xA5);

  */

  bool Dropper::drop_item(u32 item) {
    u32 x, y;

    if (drop_check(x, y)) {
      return drop_item_to_position(item, x, y);
    }

    return false;
  }

  bool Dropper::drop_item_to_position(u32 item, u32 x, u32 y) {
    
  }
} // namespace CTRPluginFramework::ACNL
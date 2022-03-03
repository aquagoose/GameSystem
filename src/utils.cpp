#include "gamesystem.h"

namespace gamesystem
{
  Color color(byte r, byte g, byte b)
  {
    r >>= 3;
    g >>= 2;
    b >>= 3;

    return r << 11 | g << 5 | b;
  }

  Color color(uint32_t value)
  {
    return color(value >> 16, (value >> 8) & 0xFF00, value & 0xFF);
  }
}

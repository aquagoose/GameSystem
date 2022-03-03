#include "gamesystem.h"

namespace gamesystem
{
  Framebuffer* createFramebuffer(uint16_t width, uint16_t height)
  {
    Framebuffer stackBuf = { width, height };
    Framebuffer* buf = malloc(sizeof(Framebuffer));
    memcpy(buf, &stackBuf, sizeof(*buf));
    buf->data = malloc(sizeof(Color) * width * height);
    return buf;
  }

  void setFramebuffer(Framebuffer* buf)
  {
    _currentBuffer = buf;
  }

  void resetFramebuffer()
  {
    _currentBuffer = &_mainBuffer;
  }

  Sprite getFramebufferAsSprite(Framebuffer* buf)
  {
    return { buf->width, buf->height, buf->data, false, 0x0000 };
  }
}

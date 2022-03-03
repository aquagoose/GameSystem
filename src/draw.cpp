#include "gamesystem.h"

namespace gamesystem
{
  void clear(Color color)
  {
    Framebuffer* buf = _currentBuffer;
    for (int i = 0; i < buf->width * buf->height; i++)
      buf->data[i] = color;
  }

  void drawPixel(Color color, Point position)
  {
    Framebuffer* buf = _currentBuffer;
    if (buf == &_mainBuffer)
      buf->data[(buf->width - position.x - 2) * buf->height + (buf->height + position.y)] = color;
    else
      buf->data[position.x * buf->width + position.y] = color;
  }

  void drawSprite(Sprite sprite, Point position)
  {
    Framebuffer* buf = _currentBuffer;
    bool isMainBuffer = buf == &_mainBuffer;
    int xValue = position.x < 0 ? -position.x : 0;
    int yValue = position.y < 0 ? -position.y : 0;
    int pX = xValue, pY = 0;
    for (int x = xValue; x < sprite.width; x++)
    {
      pY = yValue;
  
      if (pX + position.x >= buf->width)
        break;
      for (int y = yValue; y < sprite.height; y++)
      {
        if (pY + position.y >= buf->height)
          break;
  
        int py = pY + position.y;
        int px = pX + position.x;
        int fbPos;
        if (isMainBuffer)
          fbPos = (buf->width - px - 2) * buf->height + (buf->height + py);
        else
          fbPos = py * buf->width + px;
        int texPos = y * sprite.width + x;
        if (!sprite.transparentPixel || sprite.data[texPos] != sprite.transparentPixelColor)
          buf->data[fbPos] = sprite.data[texPos];
        pY++;
      }
      pX++;
    }
  }

  void drawSprite(Sprite sprite, Point position, float scaleX, float scaleY)
  {
    Framebuffer* buf = _currentBuffer;
    bool isMainBuffer = buf == &_mainBuffer;
    float inverseScaleX = 1 / scaleX;
    float inverseScaleY = 1 / scaleY;
    
    float xValue = position.x < 0 ? -position.x * inverseScaleX : 0;
    float yValue = position.y < 0 ? -position.y * inverseScaleY : 0;
    int pX = xValue, pY = 0;
    for (float x = xValue; x < sprite.width; x += inverseScaleX)
    {
      pY = yValue;
  
      if (pX + position.x >= buf->width)
        break;
      for (float y = yValue; y < sprite.height; y += inverseScaleY)
      {
        if (pY + position.y >= buf->height)
          break;
        int ix = (int) x;
        int iy = (int) y;
        int py = pY + position.y;
        int px = pX + position.x;
        int fbPos;
        if (isMainBuffer)
          fbPos = (buf->width - px - 2) * buf->height + (buf->height + py);
        else
          fbPos = py * buf->width + px;
        int texPos = iy * sprite.width + ix;
        if (!sprite.transparentPixel || sprite.data[texPos] != sprite.transparentPixelColor)
          buf->data[fbPos] = sprite.data[texPos];
        pY++;
      }
      pX++;
    }
  }

  void drawSprite(Sprite sprite, Point position, float scale)
  {
    drawSprite(sprite, position, scale, scale);
  }
}

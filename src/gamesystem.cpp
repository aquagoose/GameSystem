#include "gamesystem.h"

namespace gamesystem
{
  const Framebuffer _mainBuffer = { DISP_WIDTH, DISP_HEIGHT, malloc(sizeof(Color) * DISP_WIDTH * DISP_HEIGHT) };
  const DMAMEM Framebuffer _syncBuffer = { DISP_WIDTH, DISP_HEIGHT, malloc(sizeof(Color) * DISP_WIDTH * DISP_HEIGHT) };
  
  Framebuffer* _currentBuffer = &_mainBuffer;
}

using namespace gamesystem;

ILI9341_T4::ILI9341Driver _tft(_PIN_CS, _PIN_DC, _PIN_SCK, _PIN_MOSI, _PIN_MISO, _PIN_RESET);

int main()
{
  _tft.begin(_SPI_SPEED);
  _tft.setRotation(0);
  _tft.setFramebuffers(_syncBuffer.data);
  _tft.setDiffBuffers(&_diff1, &_diff2);
  _tft.setRefreshRate(120);
  _tft.setVSyncSpacing(2);

  // clear the array of garbage data
  clear(0x0000);
  initialize();

  pinMode(_PIN_BACKLIGHT, OUTPUT);
  digitalWrite(_PIN_BACKLIGHT, HIGH);

  while (true)
  {
    update();
    draw();
    _tft.update(_mainBuffer.data);
  }
}

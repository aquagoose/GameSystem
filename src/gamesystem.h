#ifndef GAMESYSTEM_HEADER
#define GAMESYSTEM_HEADER

#include <Arduino.h>
#include <ILI9341_T4.h>

void initialize();
void update();
void draw();

namespace gamesystem
{
  // Constants ----------------------------------------------------
  #define DISP_WIDTH 320
  #define DISP_HEIGHT 240
  
  // Typedef structures -------------------------------------------
  
  typedef uint16_t Color;
  
  typedef struct
  {
    uint16_t width;
    uint16_t height;
    Color*  data;
    bool transparentPixel;
    Color transparentPixelColor;
  } Sprite;
  
  typedef struct
  {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t advance;
    int16_t offsetX;
    int16_t offsetY;
  } Character;
  
  typedef struct
  {
    uint8_t fontSize;
    Character* characters;
    Sprite* sprite;
    uint8_t rangeMax;
  } Font;

  typedef struct
  {
    int x;
    int y;
  } Point;

  typedef struct
  {
    int width;
    int height;
  } Size;

  typedef struct
  {
    int x;
    int y;
    int width;
    int height;
  } Rectangle;

  // Display functions and framebuffers

  typedef struct
  {
    const uint16_t width;
    const uint16_t height;
    Color* data;
  } Framebuffer;

  // MainBuffer is our primary framebuffer. All draw calls will eventually go through this framebuffer.
  // SyncBuffer is our vertical sync framebuffer.
  extern const Framebuffer _mainBuffer;
  extern const DMAMEM Framebuffer _syncBuffer;

  // Our two differential buffers for the display driver.
  // Users can define their own diff buffer size if they wish.
  #ifndef DIFFBUF_SIZE
  #define DIFFBUF_SIZE 6000
  #endif
  const ILI9341_T4::DiffBuffStatic<DIFFBUF_SIZE> _diff1;
  const ILI9341_T4::DiffBuffStatic<DIFFBUF_SIZE> _diff2;

  extern Framebuffer* _currentBuffer;

  Framebuffer* createFramebuffer(uint16_t height, uint16_t width);
  void setFramebuffer(Framebuffer* buffer);
  void resetFramebuffer();
  Size getCurrentFramebufferSize();
  Sprite getFramebufferAsSprite(Framebuffer* buffer);

  #define _PIN_SCK 13
  #define _PIN_MISO 12
  #define _PIN_MOSI 11
  #define _PIN_DC 10
  #define _PIN_CS 9
  #define _PIN_RESET 6
  #define _PIN_BACKLIGHT 14
  #define _SPI_SPEED 60000000

  // Draw functions -------------------------------------------

  void clear(Color color);

  void drawPixel(Color color, Point position);

  void drawSprite(Sprite sprite, Point position);
  void drawSprite(Sprite sprite, Point position, float scale);
  void drawSprite(Sprite sprite, Point position, float scaleX, float scaleY);
  void drawSprite(Sprite sprite, Point position, Rectangle sourceRect);
  void drawSprite(Sprite sprite, Point position, Rectangle sourceRect, float scaleX, float scaleY);

  // Utilities ------------------------------------------------

  Color color(byte r, byte g, byte b);
  Color color(uint32_t value);
}

#endif

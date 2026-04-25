#pragma once
#include <cstdint>

struct Pixel {
  uint8_t r, g, b, a;
  
  constexpr Pixel() :
    r{}, g{}, b{}, a{} {}
  constexpr Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    r{r}, g{g}, b{b}, a{a} {}
};

namespace Colors {
  constexpr Pixel RED{0xff, 0x00, 0x00, 0xff}; 
  constexpr Pixel GREEN{0x00, 0xff, 0x00, 0xff}; 
  constexpr Pixel BLUE{0x00, 0x00, 0xff, 0xff}; 
  constexpr Pixel BLACK{0x00, 0x00, 0x00, 0xff}; 
}

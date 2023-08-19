#include <ch32v30x.h>
#include "globals.h"

void ws2812Init();
void ws2812SetLed(uint16_t idx, uint32_t rgb);
void ws2812Fill(uint32_t rgb);
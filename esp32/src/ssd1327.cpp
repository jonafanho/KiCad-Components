#include "ssd1327.h"
#include <U8g2lib.h>

SSD1327::SSD1327() : DisplayDriver(128, 96) {}

bool SSD1327::initRaw()
{
    return U8G2_SSD1327_VISIONOX_128X96_F_4W_SW_SPI(U8G2_R0, PIN_CLK, PIN_MOSI, PIN_CS, PIN_DC).begin();
}

void SSD1327::pushRaw()
{
    // Column address
    send(0x15, false);
    send(0, false);
    send(screenWidth / 2 - 1, false);

    // Row address
    send(0x75, false);
    send(0, false);
    send(screenHeight - 1, false);

    // Write data into RAM
    for (uint16_t i = 0; i < screenWidth * screenHeight / 2; i++)
    {
        send(buffer[i], true);
    }
}

void SSD1327::send(uint8_t value, bool isData)
{
    gpio_set_level(PIN_CS, 0);
    gpio_set_level(PIN_DC, isData ? 1 : 0);

    for (uint8_t i = 0; i < 8; i++)
    {
        gpio_set_level(PIN_CLK, 0);
        gpio_set_level(PIN_MOSI, (value & 0x80) ? 1 : 0);
        asm volatile("nop\n");
        gpio_set_level(PIN_CLK, 1);
        value <<= 1;
    }

    gpio_set_level(PIN_CS, 1);
}

#include "ssd1309.h"
#include <U8g2lib.h>

SSD1309::SSD1309() : DisplayDriver(128, 32) {}

bool SSD1309::initRaw()
{
    return U8G2_SSD1309_128X64_NONAME0_F_8080(U8G2_R0, PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, PIN_WR, PIN_CS, PIN_DC).begin();
}

void SSD1309::pushRaw()
{
    // Horizontal addressing mode
    send(0x20, false);
    send(0x00, false);

    // Column address
    send(0x21, false);
    send(0, false);
    send(screenWidth - 1, false);

    // Page address
    send(0x22, false);
    send(4, false);
    send(7, false);

    for (uint16_t y = 0; y < screenHeight; y += 8)
    {
        for (uint16_t x = 0; x < screenWidth; x++)
        {
            uint8_t data = 0;
            for (uint8_t i = 0; i < 8; i++)
            {
                bool pixel = buffer[x / 2 + (y + i) * screenWidth / 2] & (x % 2 == 0 ? 0xF0 : 0x0F);
                data |= (pixel ? 1 : 0) << i;
            }
            send(data, true);
        }
    }
}

void SSD1309::send(uint8_t value, bool isData)
{
    // Set individual data bits using ESP-IDF low-level API
    gpio_set_level(PIN_D0, (value & 0x01) ? 1 : 0);
    gpio_set_level(PIN_D1, (value & 0x02) ? 1 : 0);
    gpio_set_level(PIN_D2, (value & 0x04) ? 1 : 0);
    gpio_set_level(PIN_D3, (value & 0x08) ? 1 : 0);
    gpio_set_level(PIN_D4, (value & 0x10) ? 1 : 0);
    gpio_set_level(PIN_D5, (value & 0x20) ? 1 : 0);
    gpio_set_level(PIN_D6, (value & 0x40) ? 1 : 0);
    gpio_set_level(PIN_D7, (value & 0x80) ? 1 : 0);

    // Set control pins
    gpio_set_level(PIN_CS, 0);
    gpio_set_level(PIN_DC, isData ? 1 : 0);

    // Pulse WR low then high
    gpio_set_level(PIN_WR, 0);
    asm volatile("nop\n");
    gpio_set_level(PIN_WR, 1);
    gpio_set_level(PIN_CS, 1);
}

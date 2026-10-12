#include "ssd1322.h"
#include <U8g2lib.h>

SSD1322::SSD1322() : DisplayDriver(256, 64) {}

bool SSD1322::initRaw()
{
    return U8G2_SSD1322_NHD_256X64_F_8080(U8G2_R0, PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, PIN_WR, PIN_CS, PIN_DC).begin();
}

void SSD1322::pushRaw()
{
    // Column address
    send(0x15, false);
    send(28, true);
    send(28 + screenWidth / 4 - 1, true);

    // Row address
    send(0x75, false);
    send(0, true);
    send(screenHeight - 1, true);

    // Write data into RAM
    send(0x5C, false);

    for (uint16_t i = 0; i < screenWidth * screenHeight / 2; i++)
    {
        send(buffer[i], true);
    }
}

void SSD1322::send(uint8_t value, bool isData)
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

#include "display_driver.h"

DisplayDriver::DisplayDriver(const uint16_t screenWidth, const uint16_t screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
    buffer = std::vector<uint8_t>(screenWidth * screenHeight / 2);
}

bool DisplayDriver::init()
{
    return initRaw();
}

void DisplayDriver::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0);
}

void DisplayDriver::drawPixel(uint16_t x, uint16_t y, uint8_t brightness)
{
    drawPixel(x, y, brightness, true);
}

void DisplayDriver::push()
{
    pushRaw();
}

void DisplayDriver::drawPixel(uint16_t x, uint16_t y, uint8_t brightness, bool replace)
{
    if (x >= screenWidth || y >= screenHeight)
    {
        return;
    }

    uint16_t index = x / 2 + y * screenWidth / 2;

    if (x % 2 == 0)
    {
        buffer[index] = ((brightness & 0x0F) << 4) | (buffer[index] & (replace ? 0x0F : 0xFF));
    }
    else
    {
        buffer[index] = (buffer[index] & (replace ? 0xF0 : 0xFF)) | (brightness & 0x0F);
    }
}

void DisplayDriver::initAll()
{
    pinMode(PIN_SCREEN_ENABLE, OUTPUT);
    pinMode(PIN_RST, OUTPUT);
    digitalWrite(PIN_SCREEN_ENABLE, HIGH);
    delay(100);
    digitalWrite(PIN_RST, LOW);
    delay(10);
    digitalWrite(PIN_RST, HIGH);
}

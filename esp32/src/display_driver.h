#pragma once

#include <Arduino.h>
#include <vector>

class DisplayDriver
{
public:
    const uint16_t screenWidth;
    const uint16_t screenHeight;

    DisplayDriver(const uint16_t screenWidth, const uint16_t screenHeight);
    bool init();
    void clear();
    void drawPixel(uint16_t x, uint16_t y, uint8_t brightness);
    void push();
    static void initAll();

protected:
    std::vector<uint8_t> buffer;
    std::vector<uint8_t> pixelBuffer;

    virtual bool initRaw() = 0;
    virtual void pushRaw() = 0;
    void drawPixel(uint16_t x, uint16_t y, uint8_t brightness, bool replace);

private:
    static constexpr gpio_num_t PIN_SCREEN_ENABLE = GPIO_NUM_18;
    static constexpr gpio_num_t PIN_RST = GPIO_NUM_3;
};

#pragma once

#include "display_driver.h"

class SSD1309 : public DisplayDriver
{
public:
    SSD1309();
    bool initRaw() override;
    void pushRaw() override;

private:
    static constexpr gpio_num_t PIN_D0 = GPIO_NUM_11;
    static constexpr gpio_num_t PIN_D1 = GPIO_NUM_12;
    static constexpr gpio_num_t PIN_D2 = GPIO_NUM_13;
    static constexpr gpio_num_t PIN_D3 = GPIO_NUM_14;
    static constexpr gpio_num_t PIN_D4 = GPIO_NUM_21;
    static constexpr gpio_num_t PIN_D5 = GPIO_NUM_47;
    static constexpr gpio_num_t PIN_D6 = GPIO_NUM_48;
    static constexpr gpio_num_t PIN_D7 = GPIO_NUM_45;

    static constexpr gpio_num_t PIN_WR = GPIO_NUM_10;
    static constexpr gpio_num_t PIN_DC = GPIO_NUM_9;
    static constexpr gpio_num_t PIN_CS = GPIO_NUM_8;

    static void send(uint8_t value, bool isData);
};

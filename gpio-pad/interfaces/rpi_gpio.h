#pragma once

#include <mutex>
#include <optional>

namespace if_rpi_gpio
{
    namespace detail
    {
        extern volatile unsigned *gpio;
        extern std::mutex mtx;
        const int MINPIN = 0;
        const int MAXPIN = 27;
        void initPort(std::optional<int> port); // if_rpi_gpio ignores port
        void initPin(std::optional<int> port, int pin); // if_rpi_gpio ignores port
    }
    void setPin(std::optional<int> port, int pin, bool value);
    bool getPin(std::optional<int> port, int pin);
}

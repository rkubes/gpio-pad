#include "rpi_gpio.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string>

#include "../common.h"

using namespace std;

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#define BCM2708_PERI_BASE        0x0
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

namespace if_rpi_gpio
{
    volatile unsigned *detail::gpio = NULL;

    mutex detail::mtx;

    inline void detail::initPort(std::optional<int> port)
    {
        if (detail::gpio != NULL) return;

        int mem_fd, err;
        void *gpio_map;
        if ((mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC)) < 0)
        {
            throw runtime_error("if_rpi_gpio: Can't open /dev/gpiomem");
        }

        gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
        err = errno; //Hold it just in case it failed.
        close(mem_fd); //No need to keep mem_fd open after mmap

        if (gpio_map == MAP_FAILED)
        {
            LOGIT("if_rpi_gpio: mmap error " << err);
            throw runtime_error("if_rpi_gpio: mmap error");
        }

        detail::gpio = reinterpret_cast<volatile unsigned *>(gpio_map);
    }

    inline void detail::initPin(std::optional<int> port, int pin)
    {
        if (pin < detail::MINPIN || pin > detail::MAXPIN)
        {
            LOGIT("if_rpi_gpio: pin out of range! Wanted: " << pin << " Min: " << detail::MINPIN << " Max: " << detail::MAXPIN);
            throw out_of_range("if_rpi_gpio: pin out of range!");
        }

        initPort(port);

        *(detail::gpio + ((pin) / 10)) &= ~(7 << (((pin) % 10) * 3));
        *(detail::gpio + ((pin) / 10)) |=  (1 << (((pin) % 10) * 3));
    }

    void setPin(std::optional<int> port, int pin, bool value)
    {
        lock_guard<mutex> lock(detail::mtx);
        detail::initPin(port, pin);
        *(value ? detail::gpio + 7 : detail::gpio + 10) = 1<<pin;
    }

    bool getPin(std::optional<int> port, int pin)
    {
        //lock_guard<mutex> lock(detail::mtx);
        detail::initPin(port, pin);
        return *(detail::gpio+13) & (1<<pin);
    }
}

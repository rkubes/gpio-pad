#include <thread>
#include <map>
#include <linux/joystick.h>

#include "interfaces/rpi_gpio.h"
#include "common.h"

class CPadThread
{
public:
    void start(std::map<uint8_t, int> padMap, std::string devPath);

private:
    void listen();
    std::map<uint8_t, int> m_PadMap;
    std::string m_DevPath;
    std::thread m_Thread;
    int m_JoyFd;
    struct js_event m_JoyEvent;
};

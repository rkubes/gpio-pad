#include <fcntl.h>
#include <stdio.h>

#include "pad_thread.h"

void CPadThread::start(std::map<uint8_t, int> padMap, std::string devPath)
{
    m_PadMap = padMap;
    m_DevPath = devPath;
    m_Thread = std::thread(&CPadThread::listen, this);
}

void CPadThread::listen()
{
    try
    {
        LOGIT("Thread started for " << m_DevPath);

        if ((m_JoyFd = open(m_DevPath.c_str(), O_RDONLY)) == -1)
        {
            throw std::runtime_error("Could not open " + m_DevPath);
        }
        // Initialize all pins in the map:
        for (auto it = m_PadMap.begin(); it != m_PadMap.end(); it++)
        {
            if_rpi_gpio::setPin(0, it->second, false);
        }
        while (read(m_JoyFd, &m_JoyEvent, sizeof(m_JoyEvent)) == sizeof(m_JoyEvent))
        {
            if (m_JoyEvent.type == JS_EVENT_BUTTON)
            {
                //TODO: Remap joystick button depending on type of joystick
                auto it = m_PadMap.find(m_JoyEvent.number);
                if (it == m_PadMap.end())
                {
                    LOGIT("Unmapped button " << (m_JoyEvent.value ? "pressed: " : "released: ") << m_DevPath << " Button: " << static_cast<int>(m_JoyEvent.number));
                }
                else
                {
                    if_rpi_gpio::setPin(0, it->second, m_JoyEvent.value);
                    LOGIT("Mapped button " << (m_JoyEvent.value ? "pressed: " : "released: ") << m_DevPath << " Button: " << static_cast<int>(m_JoyEvent.number) << " GPIO: " << it->second);
                }
            }
        }
        throw std::runtime_error("Could not read joystick event: " + m_DevPath);
    }
    catch (const std::exception &e)
    {
        LOGIT("Critical Exception: " << e.what());
    }
    catch (...)
    {
        LOGIT("Critical Unhandled Exception!");
    }
    //TODO: Need thread cleanup, to avoid exception
}

/**
 * \file
 * \brief Common functions and macros shared throughout the project.
 * \author Russ Kubes
 *
 */

#include "common.h"

#include <sstream>
#include <iomanip>
#include <time.h>

namespace rk_common
{
    static pthread_mutex_t* getMutex()
    {
        pthread_mutex_t *mutex = new pthread_mutex_t;
        pthread_mutex_init(mutex, NULL);
        return mutex;
    }
    pthread_mutex_t* LockIO::mutex = getMutex();

    /**
     * \brief Get the current date, time, and thread ID.
     * \param abbr Set to true when this string should be abbreviated.
     * \return The requested time string for logging.
     *
     * Typically the format is: \"<b>Sun 2019-04-21 18:45:37.456> (121)</b>\" \n
     * In this example, the thread ID was **121**.
     *
     * The abbreviated format is as follows: \"<b>04/21_18:45:37 </b>\" \n
     * This may be useful for SMS communications.
     */
    std::string getTime(bool abbr)
    {
        struct timespec ts;
        struct tm * timeinfo;
        timespec_get(&ts, TIME_UTC);
        timeinfo = localtime(&ts.tv_sec);

        const char days[7][5] = {"Sun ", "Mon ", "Tue ", "Wed ", "Thu ", "Fri ", "Sat "};

        std::stringstream out;
        out.fill('0');

        if (abbr)
        {
            out << std::setw(2)
                << timeinfo->tm_mon + 1 << "/"
                << std::setw(2)
                << timeinfo->tm_mday << "_"
                << std::setw(2)
                << timeinfo->tm_hour << ":"
                << std::setw(2)
                << timeinfo->tm_min << ":"
                << std::setw(2)
                << timeinfo->tm_sec << " ";
        }
        else
        {
            out << days[timeinfo->tm_wday] << timeinfo->tm_year + 1900 << "-"
                << std::setw(2)
                << timeinfo->tm_mon + 1 << "-"
                << std::setw(2)
                << timeinfo->tm_mday << " "
                << std::setw(2)
                << timeinfo->tm_hour << ":"
                << std::setw(2)
                << timeinfo->tm_min << ":"
                << std::setw(2)
                << timeinfo->tm_sec << "."
                << std::setw(3)
                << (ts.tv_nsec / 1000000) << " ";
        }

        return out.str();
    }
}

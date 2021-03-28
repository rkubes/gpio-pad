/**
 * \file
 * \brief Common functions and macros shared throughout the project.
 * \author Russ Kubes
 *
 */

#pragma once

#include <iostream>
#include <unistd.h>
#include <string>
#include <stdexcept>
#include <sys/syscall.h>

#define __METHOD_NAME__ rk_common::methodName(__PRETTY_FUNCTION__)

/**
 * \brief Write text to stderr, prepended by the date, time, and thread number.
 * \param e The text that should be written to stderr.
 */
#define LOGIT(e) {rk_common::LockIO lock; std::cerr << rk_common::getTime(false) << \
    "(" << syscall(SYS_gettid) << " " << __METHOD_NAME__ << ") " << e << std::endl;}

namespace rk_common
{
    std::string logSpace();
    std::string getTime(bool abbr);

    inline std::string methodName(const std::string &prettyFunction)
    {
        size_t colons = prettyFunction.find("::");
        size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
        size_t end = prettyFunction.rfind("(") - begin;
        return prettyFunction.substr(begin,end);
    }

    /**
     * \brief A locking mutex to ensure the *logit* macro always finishes writing to *stderr* before the next call.
     */
    class LockIO
    {
        static pthread_mutex_t *mutex;
    public:
        LockIO() { pthread_mutex_lock( mutex ); }
        ~LockIO() { pthread_mutex_unlock( mutex ); }
    };

    struct UserErrorException : public virtual std::runtime_error
    {
        UserErrorException(const char* message) : std::runtime_error(message) {}
        UserErrorException(const std::string & message) : std::runtime_error(message) {}
    };
}

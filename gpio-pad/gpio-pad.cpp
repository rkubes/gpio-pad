/*!
 * \file
 * \brief gpio-pad executable entry point
 * \author Russ Kubes
 *
 * \mainpage gpio-pad daemon
 * \section intro_sec Introduction
 * Gpio-pad is the executable daemon for listening for joystick inputs and updating the Raspberry Pi GPIO outputs.
  * \section compile_sec Compilation
 * \subsection Step1 Dependencies
 * First ensure all git submodules are updated to get third-party source.
  * \subsection Step2 Make
 * Run the "make" command from within the parent folder
 * \subsection Step3 Install
 * TODO: Determine steps
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <memory>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "common.h"
#include "pad_thread.h"

/*! \brief the path where the configuration file will be stored. */
#define GPIO_PAD_CONF "/etc/gpio-pad.json"

#define GPIO_PAD_VERSION "v0.1b"

using namespace std;

int main()
{
    cerr << "--------------------------------------------------------------------------------" << endl;
    LOGIT("Starting gpio-pad version: " GPIO_PAD_VERSION);

/* TODO: Load configuration file
         Create structs for controller mapping by identifier (maybe device name or MAC?), to map button numbers to other numbers
             This will be used so that controllers with different layouts won't need a different GPIO mapping
             Example, the user can ensure the "right trigger" always is considered button '8' on various models
         Create structs for mapping button numbers to GPIO pins
             There will be a struct for each "player" - so "js1" can trigger different GPIOs from "js0"
             The array to track threads for different controllers can be 'dynamically' sized at runtime based on the number configured
 */

    //const int bufferSize = 256; // This doesn't NEED to be large enough to fit the whole file.
    try
    {
        /* TODO: Open the configuration file
        unique_ptr<char[]> buffer;
        FILE* configFile = fopen(GPIO_PAD_CONF, "r");
        if (configFile == nullptr) throw runtime_error("Could not read " GPIO_PAD_CONF);
        buffer.reset(new char[bufferSize]);
        rapidjson::FileReadStream configStream(configFile, buffer.get(), bufferSize);
        rapidjson::Document configJSON;
        if (configJSON.ParseStream<rapidjson::kParseCommentsFlag>(configStream).HasParseError())
        {
            fclose(configFile);
            throw runtime_error("Could not parse " GPIO_PAD_CONF);
        }
        fclose(configFile);
        buffer.reset();
        */

        // TODO: Read values from config
        // Below is just a "hard coded" map of the JS1 buttons to GPIO pins for proof of concept
        map<uint8_t, int> pad_mapping { {16, 16}, {15, 17}, {14, 18}, {13, 19}, {9, 20}, {8, 21}, {3, 22}, {0, 23} };

        if (access("/dev/input/js0", R_OK)) throw runtime_error("Could not read /dev/input/js0!");
        CPadThread player1;
        // TODO: Set lights, monitor for "time out" to disconnect joystick
        player1.start(pad_mapping, "/dev/input/js0");
        // ^^ This starts another thread, now need to keep main busy/alive
        string str; // Eventually replace this with loops monitoring threads, (re)starting as js devices become available, etc..
        cin >> str;
    }
    catch (const exception &e)
    {
        LOGIT("Critical Exception: " << e.what());
        return -1;
    }
    catch (...)
    {
        LOGIT("Critical Unhandled Exception!");
        return -1;
    }

    return 0;
}

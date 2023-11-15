#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

const std::string SETLEDS_CMD = "/usr/bin/setleds";
const double CHECK_INTERVAL = 0.1;
const std::string CONSOLE = "/dev/console";
const std::string INDICATOR = "scroll";

std::string getVmstat() {
    std::ifstream vmstatFile("/proc/vmstat");
    std::stringstream buffer;
    buffer << vmstatFile.rdbuf();
    return buffer.str();
}

void led_on() {
    std::string command = SETLEDS_CMD + " -L +" + INDICATOR + " < " + CONSOLE;
    system(command.c_str());
}

void led_off() {
    std::string command = SETLEDS_CMD + " -L -" + INDICATOR + " < " + CONSOLE;
    system(command.c_str());
}

int main() {
    std::string newVmstat = getVmstat();
    std::string oldVmstat = getVmstat();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(CHECK_INTERVAL)));

        newVmstat = getVmstat();

        if (newVmstat == oldVmstat) {
            led_off();
        } else {
            led_on();
        }

        oldVmstat = newVmstat;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

const std::string SETLEDS_CMD = "/usr/bin/setleds";
const double CHECK_INTERVAL = 0.1;
const std::string CONSOLE = "/dev/console";
const std::string INDICATOR = "scroll";
const std::string DISKSTATS_PATH = "/proc/diskstats";

std::string getDiskstats() {
    std::ifstream diskstatsFile(DISKSTATS_PATH);
    std::stringstream buffer;
    buffer << diskstatsFile.rdbuf();
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
    std::string newDiskstats = getDiskstats();
    std::string oldDiskstats = getDiskstats();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(CHECK_INTERVAL)));

        newDiskstats = getDiskstats();

        if (newDiskstats == oldDiskstats) {
            led_off();
        } else {
            led_on();
        }

        oldDiskstats = newDiskstats;
    }

    return 0;
}

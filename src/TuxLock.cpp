//
// Created by c2c on 6/3/18.
//

#include <iostream>
#include <vector>
#include <parted/parted.h>
#include "TuxLock.hpp"

TuxLock::TuxLock::TuxLock() {
    this->console = spdlog::stdout_color_mt("console");
    spdlog::set_pattern("%^%v%$");
#ifdef TL_DEBUG
    this->console->debug("Enabling debug mode");
    spdlog::set_level(spdlog::level::debug);
#endif
};

std::vector<TuxLock::Drive::Generic*> TuxLock::TuxLock::findDrives() {
    ped_device_probe_all();
    std::vector<Generic*> disks;
    try {
#ifdef TL_DEBUG
        this->console->debug("Getting first device...");
#endif
        PedDevice * device = ped_device_get_next(nullptr);
        if(device == nullptr) {
#ifdef TL_DEBUG
            this->console->debug("No devices found...");
#endif
            exit(0);
        }
        while (device != nullptr) {
            disks.push_back(new Generic(device->path));
#ifdef TL_DEBUG
            this->console->debug("Disk: {0}", device->path);
#endif
            device = ped_device_get_next(device);
        }
        return disks;
    } catch (std::exception &exception) {
        this->console->error(exception.what());
        exit(0);
    }
}

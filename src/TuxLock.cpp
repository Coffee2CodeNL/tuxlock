/*
 *    TuxLock
 *    Copyright (C) 2018 Coffee2CodeNL (github.com/Coffee2CodeNL)
 *
 *    This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Project           :   TuxLock
 *    File              :   TuxLock.cpp
 */
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

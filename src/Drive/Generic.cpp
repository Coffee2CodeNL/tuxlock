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
 *    File              :   Generic.cpp
 */
#include "Generic.hpp"

TuxLock::Drive::Generic::Generic(char *driveRef) {
    this->drivePath = driveRef;
    this->driveHandle = 0;
    if (strncmp(driveRef, "/dev/nvme", 9) == 0) {
#ifdef TL_DEBUG
        this->console->debug("Is a NVMe Drive");
#endif
        std::regex regex("/dev/nvme[0-9]");
        std::cmatch matchResults;
        if (std::regex_search(this->drivePath.c_str(), matchResults, regex, std::regex_constants::match_any)) {
#ifdef TL_DEBUG
            this->console->debug("I'm guessing we got {0}", matchResults[0]);
#endif
            this->drivePath = matchResults[0];
        }

    } else if (strncmp(driveRef, "/dev/sd", 6) == 0) {
#ifdef TL_DEBUG
        this->console->debug("Is a SATA Drive");
#endif
    }
}

int TuxLock::Drive::Generic::getHandle() {
    if (this->driveHandle == 0) {

#ifdef TL_DEBUG
        this->console->debug("Opening {0}", this->drivePath);
#endif

        this->driveHandle = open(this->drivePath.c_str(), O_RDONLY);

#ifdef TL_DEBUG
        this->console->debug("Drive {0} opened, ref: {1}", this->drivePath, this->driveHandle);
#endif
    }

    return this->driveHandle;
}

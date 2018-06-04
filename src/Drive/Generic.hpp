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
 *    File              :   Generic.hpp
 */
#pragma once

#include <fcntl.h>
#include <regex>
#include <iostream>
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

namespace TuxLock {
    namespace Drive {
        class Generic {
        public:
            explicit Generic(char *driveRef);

            int getHandle();

            virtual std::string getPath() {return drivePath; };

        private:
            std::string drivePath;
            int driveHandle;
            std::shared_ptr<spdlog::logger> console = spdlog::get("console");
        };
    }
}


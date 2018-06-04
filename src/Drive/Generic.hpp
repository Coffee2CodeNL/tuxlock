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


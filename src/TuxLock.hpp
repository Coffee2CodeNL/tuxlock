//
// Created by c2c on 6/3/18.
//

#pragma once

#include "spdlog/spdlog.h"
#include "Drive/Generic.hpp"
using namespace TuxLock::Drive;
namespace TuxLock {
    class TuxLock {
    public:
        TuxLock();

        std::vector<Generic *> findDrives();

    private:
        std::shared_ptr<spdlog::logger> console;
    };
}


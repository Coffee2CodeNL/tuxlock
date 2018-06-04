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
 *    File              :   CLI.hpp
 */
#pragma once

#include <iostream>
#include <utility>
#include "cxxopts.hpp"
#include "rang.hpp"
#include "spdlog/spdlog.h"
#include "../TuxLock.hpp"

#ifdef TUXLOCK_CLI_EXEC_NAME

std::string getExecName()
{
    return "tuxlock-cli";
}

#endif

namespace TuxLock {
    class CLI {
    public:
        CLI(int argc, char** argv);

        void run(int argc, char* argv[]);

    protected:
        std::shared_ptr<spdlog::logger> console;
        cxxopts::Options options = cxxopts::Options(getExecName(), "SED Utility for Linux");

        void initializeOptions();

        void handleException(std::exception& exception, bool showHelp = false);

        TuxLock* tl;
    };
}


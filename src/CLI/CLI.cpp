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
 *    File              :   CLI.cpp
 */
#include "CLI.hpp"

int main(int argc, char *argv[]) {
    TuxLock::CLI cli(argc, argv);
    return 0;
}

TuxLock::CLI::CLI(int argc, char *argv[]) {
    this->tl = new TuxLock();
    this->console = spdlog::get("console");
    this->initializeOptions();
    this->run(argc, argv);
}

void TuxLock::CLI::handleException(std::exception &exception, bool showHelp) {
    this->console->warn(exception.what());
    if (showHelp) {
        std::cout << this->options.help({""}) << std::endl;
    }
    exit(0);
}

void TuxLock::CLI::initializeOptions() {
    this->options.add_options()
            ("l,lock", "Lock the drive", cxxopts::value<bool>())
            ("u,unlock", "Unlock the drive", cxxopts::value<bool>())
            ("d,device", "Path to the drive", cxxopts::value<std::string>(), "DRIVE")
            ("f,findDrives", "List all drives", cxxopts::value<bool>())
            ("h,help", "Print this help text");
}

void TuxLock::CLI::run(int argc, char *argv[]) {
    try {
        auto result = this->options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help({""}) << std::endl;
            exit(0);
        }

        if (!result.count("device")) {
            this->console->warn("No device specified");
            std::cout << options.help({""}) << std::endl;
            exit(0);
        }
        std::string drivePath = result["d"].as<std::string>();

        if (result.count("lock")) {
            bool locked = result["lock"].as<bool>();
            if (locked != 0) {
                this->console->info("Drive {0} locked", drivePath);
            }
        }

        if (result.count("unlock")) {
            bool unlocked = result["unlock"].as<bool>();
            if (unlocked != 0) {
                this->console->info("Drive {0} unlocked", drivePath);
            }
        }

        if (result.count("findDrives")) {
            if (0 < getuid()) {
#ifdef TL_DEBUG
                this->console->debug("Running as user {0}", getuid());
#endif
                this->console->error("This function requires root access");
                exit(0);
            }
            bool findDrives = result["findDrives"].as<bool>();
            if (findDrives != 0) {
#ifdef TL_DEBUG
                this->console->debug("Listing drives...");
#endif
                std::vector<Generic*> driveList = tl->findDrives();
                for (auto currentDrive : driveList) {
                    this->console->info("Currently checking {0}", currentDrive->getPath());

                }
            }
        }
    }
    catch (cxxopts::OptionParseException &parseException) {
        this->handleException(parseException, true);
    }
    catch (std::exception &exception) {
        this->handleException(exception);
    }
}



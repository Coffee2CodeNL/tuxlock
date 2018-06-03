//
// Created by c2c on 6/2/18.
//

#include <iostream>
#include "cxxopts.hpp"
#include "rang.hpp"
#include "Drive/Generic.h"
#include "TuxlockCLI.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options(argv[0], "SED Utility for Linux");
    try {
        options.add_options()
                ("l,lock", "Lock the drive", cxxopts::value<bool>())
                ("d,device", "Path to the drive", cxxopts::value<std::string>(), "DRIVE")
                ("h,help", "Print this help text");
        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help({""}) << std::endl;
            exit(0);
        }
        if (!result.count("device")) {
            std::cout << "No device specified" << std::endl;
            return 1;
        }
        std::string drivePath = result["d"].as<std::string>();
        if (result.count("lock")) {
            bool locked = result["lock"].as<bool>();
            if (locked != 0) {
                TuxlockCLI::createConsoleHeader(std::cout, "Drive Locked: " + drivePath, 40);
            }
        }
    }
    catch (cxxopts::option_not_exists_exception &optionNotExistsException) {
        std::cout << rang::bg::cyan << rang::fg::reset << optionNotExistsException.what() << rang::bg::reset
                  << std::endl << std::endl;
        std::cout << options.help({""}) << std::endl;
        exit(0);
    }
    catch (std::exception &exception) {
        std::cout << "Error occurred: " << exception.what() << std::endl;
        exit(1);
    }


    return 0;
}

std::ostream& TuxlockCLI::createConsoleHeader(std::ostream& out, std::string string, int length) {
    if (length % 2 != 0) {
        throw std::invalid_argument("Length is not divisble by two!");
    }
    string.append(length / 2 - string.length(), ' ');
    string.insert(string.begin(), length / 2 - string.length(), ' ');
    u_long strlen = string.length();
    std::string spaces = spaces;
    spaces.append((int)strlen, ' ');
    out << spaces << std::endl << string << std::endl << spaces << std::endl;
    return out;
}
#pragma once
#include <iostream>
#include <utility>
#include "cxxopts.hpp"
#include "rang.hpp"
#include "spdlog/spdlog.h"
#include "../TuxLock.hpp"

#ifdef TUXLOCK_CLI_EXEC_NAME

std::string getExecName() {
    return "tuxlock-cli";
}

#endif

namespace TuxLock {
    class CLI {
    public:
        CLI(int argc, char **argv);

        void run(int argc, char *argv[]);

    private:
        std::shared_ptr<spdlog::logger> console;
        cxxopts::Options options = cxxopts::Options(getExecName(), "SED Utility for Linux");

        void initializeOptions();

        void handleException(std::exception &exception, bool showHelp = false);

        TuxLock *tl;
    };
}


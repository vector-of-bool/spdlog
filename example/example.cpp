//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

// spdlog usage example

#include "spdlog/cfg/env.h"
#include "spdlog/spdlog.h"

#include "spdlog/sinks/stdout_color_sinks.h"

int main(int, char *[])
{
    spdlog::cfg::init_from_env();    
    auto l1 = spdlog::stderr_color_mt("logger1");
    auto l2 = spdlog::stderr_color_mt("logger2");

    
    l1->debug("Hello L1");
    l2->debug("Hello L2");
    spdlog::debug("Hello global");    
}

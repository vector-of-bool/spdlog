//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

// spdlog usage example

#include <cstdio>

void stdout_logger_example();
void basic_example();
void rotating_example();
void daily_example();
void async_example();
void binary_example();
void trace_example();
void multi_sink_example();
void user_defined_example();
void err_handler_example();
void syslog_example();


#include "spdlog/cfg.h"
#include "spdlog/spdlog.h"

#include "spdlog/sinks/stdout_color_sinks.h"

int main(int, char *[])
{
    using namespace spdlog;
    using namespace spdlog::sinks;

    auto l1 = spdlog::stderr_color_mt("logger1");
    auto l2 = spdlog::stderr_color_mt("logger2");

    spdlog::cfg::init_from_env();    
    l1->debug("Hello L1");
    l2->debug("Hello L2");
    spdlog::debug("Hello global");
    
}
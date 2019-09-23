// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "spdlog/common.h"

// config spdlog from varius sources
namespace spdlog 
{
 namespace cfg
 {
    // Config spdlog log level from the env variable SPDLOG_LEVEL 
    // Can accept multiple logger names
    // Examples:
    // export SPDLOG_LEVEL=debug 
    // export SPDLOG_LEVEL=logger1=debug,logger2=info,*=error
    void levels_from_env();

    // Config spdlog log pattern from the env variable SPDLOG_PATTERN 
    // Examples:
    // export SPDLOG_PATTERN=[%x] [%l] [%n] %v     
    // export SPDLOG_LEVEL=logger1=%v,*=[%x] [%l] [%n] %v    
    void patterns_from_env();
 }
}

#ifdef SPDLOG_HEADER_ONLY
#include "cfg-inl.h"
#endif // SPDLOG_HEADER_ONLY

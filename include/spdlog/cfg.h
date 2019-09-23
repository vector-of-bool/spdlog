// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
// config spdlog from varius sources
namespace spdlog 
{
 namespace cfg
 {
    // Config spdlog log level from the env variable SPDLOG_LEVEL 
    // e.g. SPDLOG_LEVEL=debug && ./a.out
    // Un recognized/malformed values will be ignored.
    void init_from_env();
 }
}

#ifdef SPDLOG_HEADER_ONLY
#include "cfg-inl.h"
#endif // SPDLOG_HEADER_ONLY

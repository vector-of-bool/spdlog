// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef SPDLOG_HEADER_ONLY
#include "spdlog/cfg.h"
#endif

#include "spdlog/details/os.h"
#include "spdlog/details/registry.h"

namespace spdlog {
namespace cfg {

static std::string to_lower_(const std::string &str)
{
    std::string rv = str;
    std::transform(str.begin(), str.end(), rv.begin(), [](char ch) {
        return static_cast<char>((ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch);
    });
    return rv;
}
       
SPDLOG_INLINE void from_env()
{
    auto spdlog_level = to_lower_(details::os::getenv("SPDLOG_LEVEL"));            
    auto level = level::from_str(spdlog_level);

    // set t oinfo on unknown values (level::from_str(str) returns level::off for recognized str level)
    if (level == level::off && spdlog_level != "off")
    {
        level = level::info;
    }            
    set_level(level);
}

}  // namespace cfg
} // namespace spdlog

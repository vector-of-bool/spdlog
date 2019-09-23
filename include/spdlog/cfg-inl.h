// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef SPDLOG_HEADER_ONLY
#include "spdlog/cfg.h"
#endif

#include "spdlog/spdlog.h"
#include "spdlog/details/os.h"
#include "spdlog/details/registry.h"

#include <string>
#include <tuple>
#include <sstream>

namespace spdlog {
    namespace cfg {

        SPDLOG_INLINE std::string to_lower_(const std::string &str)
        {
            std::string rv = str;
            std::transform(str.begin(), str.end(), rv.begin(), [](char ch) {
                return static_cast<char>((ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch);
            });
            return rv;
        }

        using name_val_tuple = std::tuple<std::string, std::string>;

        // return tuple with name, value from "name=value" string. replace with empty string on missing parts
        SPDLOG_INLINE name_val_tuple extract_kv_(char sep, const std::string &str)
        {
            auto n = str.find(sep);
            if (n == std::string::npos)
            {
                return std::make_tuple(std::string{}, str);
            }
            return std::make_tuple(str.substr(0, n), str.substr(n + 1));
        }

        // return name vector of value pairs from str.
        // str format: "a=A,b=B,c=C,d=D,.."
        SPDLOG_INLINE std::vector<name_val_tuple> extract_name_vals_(const std::string &str)
        {
            std::vector<name_val_tuple> rv;
            std::string token;
            std::istringstream tokenStream(str);
            while (std::getline(tokenStream, token, ','))
            {
                rv.push_back(extract_kv_('=', token));
            }
            return rv;
        }


        SPDLOG_INLINE void levels_from_env()
        {
            using details::os::getenv;
            std::string levels = getenv("SPDLOG_LEVEL");
            auto name_vals = extract_name_vals_(levels);

            // Init the global level first
            for (auto &nv : name_vals) {
                auto &logger_name = std::get<0>(nv);
                auto log_level = level::from_str(to_lower_(std::get<1>(nv)));
                if (logger_name.empty() || logger_name == "*")
                {
                    spdlog::set_level(log_level);
                    break;
                }
            }
            // Init specific loggers
            for (auto &nv : name_vals)
            {
                auto &logger_name = std::get<0>(nv);
                if (logger_name.empty() || logger_name == "*")
                {
                    continue;
                }
                auto log_level = level::from_str(to_lower_(std::get<1>(nv)));
                auto logger = spdlog::get(logger_name);
                if (logger)
                {
                    logger->set_level(log_level);
                }
            }
        }

        SPDLOG_INLINE void patterns_from_env()
        {
            using details::os::getenv;
            std::string patterns = getenv("SPDLOG_PATTERN");
            auto name_vals = extract_name_vals_(patterns);

            // Init the global level first
            for (auto &nv : name_vals) {
                auto &logger_name = std::get<0>(nv);
                auto &pattern = std::get<1>(nv);                
                if ((logger_name.empty() || logger_name == "*") && !pattern.empty())
                {
                    spdlog::set_pattern(pattern);
                    break;
                }
            }
            // Init specific loggers
            for (auto &nv : name_vals)
            {
                auto &logger_name = std::get<0>(nv);
                auto &pattern = std::get<1>(nv);
                if (logger_name.empty() || logger_name == "*" || pattern.empty())
                {
                    continue;
                }               
                auto logger = spdlog::get(logger_name);                
                if (logger)
                {
                    logger->set_pattern(pattern);
                }
            }
        }
    }  // namespace cfg
} // namespace spdlog

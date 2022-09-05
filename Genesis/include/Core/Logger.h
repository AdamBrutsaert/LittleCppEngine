#pragma once

#include <spdlog/spdlog.h>

namespace Genesis {

    class Logger {
    public:
        static void Initialize();

        static std::shared_ptr<spdlog::logger> Get();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}

#define LOG_TRACE(...) SPDLOG_LOGGER_TRACE(::Genesis::Logger::Get(), __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_INFO(::Genesis::Logger::Get(), __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_WARN(::Genesis::Logger::Get(), __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(::Genesis::Logger::Get(), __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::Genesis::Logger::Get(), __VA_ARGS__)

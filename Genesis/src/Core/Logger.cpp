#include "Precompiled.h"
#include "Core/Logger.h"

namespace Genesis {

    std::shared_ptr<spdlog::logger> Logger::s_Logger{};

    void Logger::Initialize() {
        std::time_t t = std::time(0);
        std::tm *now = std::localtime(&t);

        std::string file_sink_path = "logs/" + std::to_string(now->tm_mday) + "-" +
                                    std::to_string(now->tm_mon + 1) + "-" +
                                    std::to_string(now->tm_year + 1900) + "_" +
                                    std::to_string(now->tm_hour) + "h" +
                                    std::to_string(now->tm_min) + "m" +
                                    std::to_string(now->tm_sec) + "s.log";

        std::string file_trace_sink_path =
            "logs/" + std::to_string(now->tm_mday) + "-" +
            std::to_string(now->tm_mon + 1) + "-" +
            std::to_string(now->tm_year + 1900) + "_" + std::to_string(now->tm_hour) +
            "h" + std::to_string(now->tm_min) + "m" + std::to_string(now->tm_sec) +
            "s-trace.log";

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::info);
        console_sink->set_pattern("%^[%T] [%l]: %v%$");

       /*  auto file_sink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_sink_path, true);
        file_sink->set_level(spdlog::level::info);
        file_sink->set_pattern("%^[%@] [%T] [%l]: %v%$");

        auto file_trace_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            file_trace_sink_path, true);
        file_trace_sink->set_level(spdlog::level::trace);
        file_trace_sink->set_pattern("%^[%@] [%T] [%l]: %v%$"); */

        spdlog::sinks_init_list sinks = {console_sink, /* file_trace_sink, file_sink */};
        s_Logger = std::make_shared<spdlog::logger>("Logger", sinks);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger> Logger::Get() { return s_Logger; }

} // namespace Genesis

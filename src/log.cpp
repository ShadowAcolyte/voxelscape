#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>

#include "log.h"

static std::vector<spdlog::sink_ptr> __sinks;
static std::shared_ptr<spdlog::logger> __core_logger;

void logger::init()
{
    auto _stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#ifdef _WIN32
    _stdout_sink->set_color(spdlog::level::info, 0b1010);
#else
    _stdout_sink->set_color(spdlog::level::info, "\033[92m");
#endif // _WIN32

    std::stringstream log_file_path;
    log_file_path << "logs/voxelscape-log-";
    time_t t = std::time(nullptr);
    log_file_path << std::put_time(std::localtime(&t), "%d-%m-%Y-%H-%M-%S");
    log_file_path << ".txt";

    __sinks.push_back(_stdout_sink);
    __sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_file_path.str(), 1024 * 1024 * 5, 3));
    __core_logger = std::make_shared<spdlog::logger>("logger_core", begin(__sinks), end(__sinks));
    __core_logger->set_pattern("[%H:%M:%S] [%l] %^%v%$");
    spdlog::register_logger(__core_logger);
}

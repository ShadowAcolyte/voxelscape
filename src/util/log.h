#ifndef GAIA_LOG_H
#define GAIA_LOG_H

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace logger
{
	void init();
	// Fixed string logging
	template<typename T> inline void info(const T& msg) {
		spdlog::get("logger_core")->info(msg);
	}
	template<typename T> inline void warn(const T& msg) {
		spdlog::get("logger_core")->warn(msg);
	}
	template<typename T> inline void error(const T& msg) {
		spdlog::get("logger_core")->error(msg);
	}
	template<typename T> inline void critical(const T& msg) {
		spdlog::get("logger_core")->critical(msg);
	}
	// Format string logging
	template<typename... Args> inline void info(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->info(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void warn(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->warn(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void error(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->error(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void critical(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->critical(_format, std::forward<Args>(_args)...);
	}
}

#endif // GAIA_LOG_H

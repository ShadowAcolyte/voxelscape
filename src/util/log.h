#ifndef VOX_LOG_H
#define VOX_LOG_H

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace Logger
{
	void Init();
	// Fixed string logging
	template<typename T> inline void Info(const T& msg) {
		spdlog::get("logger_core")->info(msg);
	}
	template<typename T> inline void Warn(const T& msg) {
		spdlog::get("logger_core")->warn(msg);
	}
	template<typename T> inline void Error(const T& msg) {
		spdlog::get("logger_core")->error(msg);
	}
	template<typename T> inline void Critical(const T& msg) {
		spdlog::get("logger_core")->critical(msg);
	}
	// Format string logging
	template<typename... Args> inline void Info(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->info(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void Warn(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->warn(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void Error(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->error(_format, std::forward<Args>(_args)...);
	}
	template<typename... Args> inline void Critical(fmt::format_string<Args...> _format, Args &&..._args) {
		spdlog::get("logger_core")->critical(_format, std::forward<Args>(_args)...);
	}
}

#endif // !VOX_LOG_H

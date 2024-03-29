#include "ptlpch.h"
#include "Petal/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace ptl
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%r] %^%n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("PETAL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
} // namespace ptl

#pragma once


#include "Petal/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace ptl
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PTL_CORE_CRITICAL(...)	ptl::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define PTL_CORE_ERROR(...)		ptl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PTL_CORE_WARN(...)		ptl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PTL_CORE_INFO(...)		ptl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PTL_CORE_TRACE(...)		ptl::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define PTL_CRITICAL(...)	ptl::Log::GetClientLogger()->critical(__VA_ARGS__)
#define PTL_ERROR(...)		ptl::Log::GetClientLogger()->error(__VA_ARGS__)
#define PTL_WARN(...)		ptl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PTL_INFO(...)		ptl::Log::GetClientLogger()->info(__VA_ARGS__)
#define PTL_TRACE(...)		ptl::Log::GetClientLogger()->trace(__VA_ARGS__)
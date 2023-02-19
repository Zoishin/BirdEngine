#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace BE {

	class BE_API Log
	{
	public:
		static void Init();
	
		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr <spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
	 
}

//Core Log Macros
#define BE_CORE_ERROR(...)		::BE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BE_CORE_WARN(...)		::BE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BE_CORE_INFO(...)		::BE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BE_CORE_TRACE(...)		::BE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BE_CORE_FATAL(...)		::BE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define BE_Client_ERROR(...)	::BE::Log::GetClientLogger()->error(__VA_ARGS__)
#define BE_Client_WARN(...)		::BE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BE_Client_INFO(...)		::BE::Log::GetClientLogger()->info(__VA_ARGS__)
#define BE_Client_TRACE(...)	::BE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BE_Client_FATAL(...)	::BE::Log::GetClientLogger()->fatal(__VA_ARGS__)


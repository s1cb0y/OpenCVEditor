#pragma once

#include "AppEngine/Core.h"
#include "spdlog/spdlog.h"

namespace AppEngine{
   class Log {
   public:
      static void Init();
      static std::shared_ptr<spdlog::logger>& GetLogger(){ return s_logger;}
   private:
      static std::shared_ptr<spdlog::logger> s_logger;
   };

}
#define LOG_INFO(...) AppEngine::Log::GetLogger()->info(__VA_ARGS__);
#define LOG_ERROR(...) AppEngine::Log::GetLogger()->error(__VA_ARGS__);
#define LOG_WARNING(...) AppEngine::Log::GetLogger()->warn(__VA_ARGS__);
#define LOG_TRACE(...) AppEngine::Log::GetLogger()->trace(__VA_ARGS__);

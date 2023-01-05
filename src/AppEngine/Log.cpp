#include "AppEngine/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace AppEngine{

   std::shared_ptr<spdlog::logger> Log::s_logger;; 

   void Log::Init(){ 
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      console_sink->set_level(spdlog::level::trace);
      s_logger = std::make_shared<spdlog::logger>("AppEngineLogger", console_sink);
      spdlog::register_logger(s_logger);
   }

}
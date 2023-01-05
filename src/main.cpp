

#include "AppEngine/Application.h"
#include "AppEngine/Core.h"
#include "AppEngine/Log.h"

extern AppEngine::Application* AppEngine::CreateApplication();

int main(int, char**)
{
   
   AppEngine::Log::Init();
   LOG_INFO("Create application");
   auto app = AppEngine::CreateApplication();
   LOG_INFO("Start application");
   app->Run();

   return 0;
}

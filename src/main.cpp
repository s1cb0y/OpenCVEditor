

#include "AppEngine/Application.h"

extern AppEngine::Application* AppEngine::CreateApplication();

int main(int, char**)
{
   std::cout << "Create application" << std::endl;
   auto app = AppEngine::CreateApplication();
   std::cout << "Start application" << std::endl;
   app->Run();

   return 0;
}

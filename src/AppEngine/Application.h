#pragma once
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Layer/LayerStack.h"

namespace AppEngine{

   class Application {
   public:
      Application();
      virtual ~Application();

      Application& Get (){return *s_instance; }

      void Run();

      void PushLayer(Layer* layer);
      void PopLayer(Layer* layer);
      
   private:
      static Application* s_instance;
      LayerStack m_LayerStack;
      bool m_isRunning = true;
   };

   Application* CreateApplication();
}
#pragma once
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Layer/LayerStack.h"
#include "AppEngine/Events/Event.h"
#include "AppEngine/Events/ApplicationEvent.h"

namespace AppEngine{

   class Application {
   public:
      Application();
      virtual ~Application();

      Application& Get (){return *s_instance; }

      void Run();
      void Close();

      void OnEvent(Event &event);
      bool OnClose(WindowCloseEvent &event);

      void PushLayer(Layer* layer);
      void PopLayer(Layer* layer);
      
   private:
      static Application* s_instance;
      LayerStack m_LayerStack;
      bool m_IsRunning = true;
      bool m_IsMinimized = false;
   };

   Application* CreateApplication();
}
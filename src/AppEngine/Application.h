#pragma once
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Layer/LayerStack.h"
#include "AppEngine/Events/Event.h"
#include "AppEngine/Events/ApplicationEvent.h"
#include "AppEngine/Window.h"
#include "AppEngine/ImGui/ImGuiLayer.h"

namespace AppEngine{

   class Application {
   public:
      Application();
      virtual ~Application();

      static Application& Get (){return *s_instance; }

      Window& GetWindow(){return *m_Window;}

      void Run();
      void Close();
      bool OnWindowClose(WindowCloseEvent& e);

      void OnEvent(Event &event);      

      void PushLayer(Layer* layer);
      void PopLayer(Layer* layer);

      void PushOverlay(Layer* layer);
      
   private:
      static Application* s_instance;
      LayerStack m_LayerStack;
      bool m_IsRunning = true;
      bool m_IsMinimized = false;
      std::unique_ptr<Window> m_Window = nullptr;
      ImGuiLayer *m_ImGuiLayer = nullptr;
   };

   Application* CreateApplication();
}
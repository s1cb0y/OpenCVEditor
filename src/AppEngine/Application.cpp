#include "AppEngine/Core.h"
#include "AppEngine/Application.h"

#include <cassert>

namespace AppEngine{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

   Application* Application::s_instance = nullptr;

   Application::Application(){
      assert(("Application alreay exists!", !s_instance));
      s_instance = this;
      m_Window = std::unique_ptr<Window>(Window::Create(WindowProps()));
   }

   Application::~Application()
	{		
	}

   void Application::PushLayer(Layer* layer){
      layer->OnAttach();
      m_LayerStack.PushLayer(layer);
   }
   
   void Application::PopLayer(Layer* layer){
      layer->OnDetach();
      m_LayerStack.PopLayer(layer);
   }

   void Application::Run(){
      
      if (!m_IsMinimized){
         while(m_IsRunning){
            for (auto layer : m_LayerStack){
               layer->OnUpdate();
            }
            m_Window->OnUpdate();
         }
      }
   }

   void Application::OnEvent(Event &event){
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnClose));
   }

   bool Application::OnClose(WindowCloseEvent &event){
      m_IsRunning = false;
   }
}
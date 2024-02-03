#include "AppEngine/Core.h"
#include "AppEngine/Log.h"
#include "AppEngine/Application.h"
#include <cassert>
#include "glad/glad.h"// TODO delete if glViewPort is abstracted

namespace AppEngine{

   Application* Application::s_instance = nullptr;

   Application::Application(){
      assert(("Application alreay exists!", !s_instance));
      s_instance = this;
      m_Window = std::unique_ptr<Window>(Window::Create(WindowProps()));
      m_Window->SetEventCallBack(BIND_FN(Application::OnEvent));
      m_ImGuiLayer = new ImGuiLayer();
      PushOverlay(m_ImGuiLayer);
   }

   Application::~Application()
	{		
	}

   void Application::PushLayer(Layer* layer){
      m_LayerStack.PushLayer(layer);
      layer->OnAttach();
   }

   void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
   
   void Application::Run(){
      
      if (!m_IsMinimized){
         while(m_IsRunning){
            for (auto layer : m_LayerStack){
               layer->OnUpdate();
            }
            m_ImGuiLayer->Begin();
            for (Layer * layer : m_LayerStack){
               layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            m_Window->OnUpdate();
         }
      }
      
   }

   void Application::OnEvent(Event &event){      
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
      dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Application::OnWindowResize));

      for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it){
         if (event.Handled){
            break;
         }     
         (*it)->OnEvent(event);
      }
   }

   bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

   bool Application::OnWindowResize(WindowResizeEvent& e)
   {
      if (e.GetWidth() == 0 && e.GetHeight() == 0) {
         m_IsMinimized = true;
      }
      else {
         glViewport(0, 0, e.GetWidth(), e.GetHeight());
         m_IsMinimized = false;
      }
      
      return false;
   }


   void Application::Close(){
      m_IsRunning = false;
   }
}
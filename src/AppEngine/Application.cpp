#include "AppEngine/Application.h"
#include <cassert>

namespace AppEngine{

   Application* Application::s_instance = nullptr;

   Application::Application(){
      assert(("Application alreay exists!", !s_instance));
      s_instance = this;
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
      while(m_isRunning){

      }
   }
}
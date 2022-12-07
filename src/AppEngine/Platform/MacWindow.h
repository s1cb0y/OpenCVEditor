#pragma once

#include "AppEngine/Window.h"
#include <GLFW/glfw3.h>

namespace AppEngine{

   class MacWindow : public Window{
   public:
      MacWindow(const WindowProps& props);
      virtual ~MacWindow();

      virtual void OnUpdate() override;

      virtual unsigned int GetWidth() override {return m_Props.Width;};
      virtual unsigned int GetHeigth() override {return m_Props.Height;};

   private:
      void Init();   
      void ShutDown();
      WindowProps m_Props;
      GLFWwindow* m_Window;
      static bool s_isGlfwInitialized;
   }; 
}
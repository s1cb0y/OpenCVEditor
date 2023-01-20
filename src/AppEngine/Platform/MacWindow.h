#pragma once

#include "AppEngine/Window.h"
#include <GLFW/glfw3.h>
#include "AppEngine/Events/Event.h"
namespace AppEngine{

   class MacWindow : public Window{

   public:
      MacWindow(const WindowProps& props);
      virtual ~MacWindow();

      virtual void OnUpdate() override;

      virtual unsigned int GetWidth() override { return m_WindowData.Width;};
      virtual unsigned int GetHeight() override { return m_WindowData.Height;};
      
      inline virtual void SetEventCallBack(const EventCallBackFn& fn) override { m_WindowData.fn = fn; }
      virtual void* GetNativeWindow() const override { return m_Window;}

   private:
      void Init();
      void ShutDown();
      GLFWwindow* m_Window;
      static bool s_isGlfwInitialized;
      struct WindowData {
         WindowData(const WindowProps& props) {
            Title = props.Title;
            Height = props.Height;
            Width = props.Width;
         }
         std::string Title;
         unsigned int Height;
         unsigned int Width;
         EventCallBackFn fn;
      };
      WindowData m_WindowData;
   }; 
}
#include "AppEngine/Platform/MacWindow.h"
#include "glad/glad.h"

namespace AppEngine{
   
   static bool s_GLFWInitialized = false;
   
   Window* Window::Create(const WindowProps& props){
      return new MacWindow(props);
   }

   MacWindow::MacWindow(const WindowProps& props) 
   : m_Props(props)
	{
		Init();
	}

	MacWindow::~MacWindow()
	{
		ShutDown();
	}

   void MacWindow::Init(){
      if (!s_GLFWInitialized){
         if (GLFW_TRUE == glfwInit()){
            s_GLFWInitialized = true;
         } else {
            assert(("GLFW could not be initialized!", !s_GLFWInitialized));
         }
      }

      m_Window = glfwCreateWindow((int)m_Props.Width, (int)m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(m_Window);
		// Init glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
   }

   void MacWindow::OnUpdate(){
      glfwPollEvents();
      glfwSwapBuffers(m_Window);
   }

   void MacWindow::ShutDown(){
      glfwDestroyWindow(m_Window);
   } 
}
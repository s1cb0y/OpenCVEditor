#include "AppEngine/Core.h"
#include "AppEngine/Platform/MacWindow.h"
#include "glad/glad.h"

namespace AppEngine{
   
   static bool s_GLFWInitialized = false;
   
   static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
            APP_ASSERT("GLFW could not be initialized!", !s_GLFWInitialized);
         }
      }
      m_Window = glfwCreateWindow((int)m_Props.Width, (int)m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(m_Window);
		// Init glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

      std::cout << ("OpenGL Info:");
		std::cout << ("  Vendor: {0}", glGetString(GL_VENDOR));
		std::cout << ("  Renderer: {0}", glGetString(GL_RENDERER));
		std::cout << ("  Version: {0}", glGetString(GL_VERSION));
   }

   void MacWindow::OnUpdate(){
      glfwPollEvents();
      glfwSwapBuffers(m_Window);
   }

   void MacWindow::ShutDown(){
      glfwDestroyWindow(m_Window);
   } 
} 
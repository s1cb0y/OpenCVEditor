#include "AppEngine/Core.h"
#include "AppEngine/Platform/MacWindow.h"
#include "glad/glad.h"
#include "AppEngine/Events/ApplicationEvent.h"
#include "AppEngine/Events/KeyEvent.h"
#include "AppEngine/Events/MouseEvent.h"

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
   : m_WindowData(props)
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
      
      #if defined(APP_PLATFORM_MACOS)
         // GL 3.2 + GLSL 150
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
      #endif

      m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(m_Window);
      
      // Init glad
      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      APP_ASSERT(0 != status, "Failed to load glad");
      std::cout << ("OpenGL Info:");
      std::cout << ("  Vendor: {0}", glGetString(GL_VENDOR));
      std::cout << ("  Renderer: {0}", glGetString(GL_RENDERER));
      std::cout << ("  Version: {0}", glGetString(GL_VERSION));
      
      // Set user pointer
      glfwSetWindowUserPointer(m_Window, &m_WindowData);

      // ------- Set glfw callbacks ------------      
      glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
         WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
         WindowCloseEvent e;
         data->fn(e);
      });
      
      glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         data->Height = height;
         data->Width = width;
         WindowResizeEvent e(width, height);
         data->fn(e);
      });

      glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
      {
         WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

         switch (action)
         {
         case GLFW_PRESS:
         {
            KeyPressedEvent event(key, 0);
            data.fn(event);
            break;
         }
         case GLFW_RELEASE:
         {
            KeyReleasedEvent event(key);
            data.fn(event);
            break;
         }
         case GLFW_REPEAT:
         {
            KeyPressedEvent event(key, 1);
            data.fn(event);
            break;
         }
         }
      });

      glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
      {
         WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

         KeyTypedEvent event(keycode);
         data.fn(event);
      });

      glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
      {
         WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

         switch (action)
         {
         case GLFW_PRESS:
         {
            MouseButtonPressedEvent event(button);
            data.fn(event);
            break;
         }
         case GLFW_RELEASE:
         {
            MouseButtonReleasedEvent event(button);
            data.fn(event);
            break;
         }
         }
      });

      glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
      {
         WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

         MouseScrolledEvent event((float)xOffset, (float)yOffset);
         data.fn(event);
      });

      glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
      {
         WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

         MouseMovedEvent event((float)xPos, (float)yPos);
         data.fn(event);
      });
   }

   void MacWindow::OnUpdate(){
      glfwPollEvents();
      glfwSwapBuffers(m_Window);
   }

   void MacWindow::ShutDown(){
      glfwDestroyWindow(m_Window);
   } 
} 
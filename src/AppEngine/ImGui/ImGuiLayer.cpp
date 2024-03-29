#include "AppEngine/ImGui/ImGuiLayer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"// Will drag system OpenGL headers
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "AppEngine/Application.h"

namespace AppEngine{
   
   static void glfw_error_callback(int error, const char* description)
   {
      fprintf(stderr, "Glfw Error %d: %s\n", error, description);
   }

   ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}

   ImGuiLayer::~ImGuiLayer(){}

   void ImGuiLayer::Begin(){
      // Start the ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
   }

   void ImGuiLayer::End(){
      ImGuiIO& io = ImGui::GetIO();
	  Application& app = Application::Get();
	  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
   }

   void ImGuiLayer::OnAttach() {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
      

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();

      // Setup Platform/Renderer backends
      Application& app = Application::Get();
      GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      if (ImGui_ImplOpenGL3_Init( "#version 410") == false)
         LOG_ERROR("Could not init opengl3");
   }

   void ImGuiLayer::OnDetach(){
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();

   }

   void ImGuiLayer::OnEvent(Event& event){
      if (m_BlockEvents){
         ImGuiIO io = ImGui::GetIO();
         event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
         event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
      }
   }
   
   void ImGuiLayer::OnImGuiRender() {  
      /*static bool show = true;
      ImGui::ShowDemoWindow(&show);*/
      
   }

}
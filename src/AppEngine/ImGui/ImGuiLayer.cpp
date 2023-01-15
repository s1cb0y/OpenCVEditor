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
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   }

   void ImGuiLayer::OnAttach() {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
      //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls    

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();
      //ImGui::StyleColorsClassic();

      // Setup Platform/Renderer backends
      Application& app = Application::Get();
      GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      if (ImGui_ImplOpenGL3_Init("#version 410") == false)
         LOG_ERROR("Could not init opengl3");
   }

   void ImGuiLayer::OnDetach(){
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();

   }

   void ImGuiLayer::OnImGuiRender() {
      static bool show_another_window = true;
      ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
         if (ImGui::Button("Close Me"))
            show_another_window = false;
      ImGui::End();
   }

}
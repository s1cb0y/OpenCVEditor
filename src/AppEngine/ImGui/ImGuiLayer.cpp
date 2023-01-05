#include "AppEngine/ImGui/ImGuiLayer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"// Will drag system OpenGL headers

namespace AppEngine{
   
   static void glfw_error_callback(int error, const char* description)
   {
      fprintf(stderr, "Glfw Error %d: %s\n", error, description);
   }

   ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){
   }

   ImGuiLayer::~ImGuiLayer(){

   }

   void ImGuiLayer::OnAttach() {

   }
   void ImGuiLayer::OnDetach(){

   }

   void ImGuiLayer::OnImGuiRender() {

   }

}
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
class MainLayer : public AppEngine::Layer {
   
   bool main_window_active = true;

   virtual void OnImGuiRender() {
      // Main body of the Demo window starts here.
      if (!ImGui::Begin("OpenCV Editor", &main_window_active, ImGuiWindowFlags_MenuBar))
      {
         // Early out if the window is collapsed, as an optimization.
         ImGui::End();
         return;
      }
       ImGui::Text("Hello, world %d", 123);
       ImGui::End();
   }  

};


class OpenCVEditor : public AppEngine::Application {
public:
   OpenCVEditor() : AppEngine::Application()
   {
      PushLayer(new MainLayer);
   }

};

AppEngine::Application* AppEngine::CreateApplication(){
   return new OpenCVEditor();
}


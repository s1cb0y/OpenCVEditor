#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
#include "App/UI/UIToolsWidget.h"
//#include <opencv2/opencv.hpp>

class MainLayer : public AppEngine::Layer {
public:
   MainLayer() : AppEngine::Layer("MainLayer") {
      uiTools = new UIToolsWidget();
   }

private:   
   bool main_window_active = true;
   bool show_open_dialog = false;

   // UI Widgets
   UIToolsWidget* uiTools;

   virtual void OnImGuiRender() {
      // Main body of the Demo window starts here.
      if (!ImGui::Begin("OpenCV Editor", &main_window_active, ImGuiWindowFlags_MenuBar))
      {
         // Early out if the window is collapsed, as an optimization.
         ImGui::End();
         return;
      }
      if (show_open_dialog) {
         ShowOpenFileDialog();
      }
      // Menu Bar
      if (ImGui::BeginMenuBar())
      {       
         if (ImGui::BeginMenu("File"))
         {           
            if (ImGui::MenuItem("Open", "Ctrl+O")) { show_open_dialog = true; uiTools->Show(); }
            ImGui::EndMenu();
         }         
         ImGui::EndMenuBar();
      }
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      ImGui::Text("Please start by opening a new image file");
      
      uiTools->Render();
      
      ImGui::End();
   }  

   void ShowOpenFileDialog(){
      ImGui::Begin("Open image file", &show_open_dialog);   
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
         show_open_dialog = false;
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


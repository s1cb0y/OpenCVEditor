#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
#include "App/UI/UITools.h"
#include "App/UI/UIMenuBar.h"
#include "AppEngine/Log.h"
//#include <opencv2/opencv.hpp>



class MainLayer : public AppEngine::Layer {
public:
   MainLayer() : AppEngine::Layer("MainLayer") {
      uiTools = new UITools();
      uiTools->Show();
      uiMenuBar = new UIMenuBar();
      uiMenuBar->Show();
   }

private:   
   bool main_window_active = true;
   // UI Widgets
   UITools* uiTools;
   UIMenuBar* uiMenuBar;

   virtual void OnImGuiRender() override {
      // Main body of the Demo window starts here.
      if (!ImGui::Begin("OpenCV Editor", &main_window_active, ImGuiWindowFlags_MenuBar))
      {
         // Early out if the window is collapsed, as an optimization.
         LOG_ERROR("Error in Imgui layer, could not begin main window!");
         ImGui::End();
         return;
      }
      
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      ImGui::Text("Please start by opening a new image file to process (File -> Open");
      
      uiTools->Render();
      uiMenuBar->Render();
      
      ImGui::End();
   }  

   virtual void OnEvent(AppEngine::Event& event) override {
      std::stringstream ss;
      ss << "Event : " << event.GetName();
      LOG_INFO(ss.str());
   };

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


#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
#include "App/UI/Components/UITools.h"
#include "App/UI/Components/UIMenuBar.h"
#include "AppEngine/UI/UIFrame.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"
//#include <opencv2/opencv.hpp>



class MainLayer : public AppEngine::Layer {
public:
   MainLayer() : AppEngine::Layer("MainLayer") {
      UITools* uiTools = new UITools(&m_appData);
      UIMenuBar* uiMenuBar = new UIMenuBar(&m_appData);
      m_uiMainFrame = new UIFrame("OpenCV Editor", ImGuiWindowFlags_MenuBar);
      m_uiMainFrame->AddWidget(uiMenuBar);
      m_uiMainFrame->AddWidget(uiTools);
   }

   ~MainLayer() {
      if (m_uiMainFrame)         
         delete m_uiMainFrame;
   }

private:   
   virtual void OnImGuiRender() override {
      m_uiMainFrame->Render();
   }  

   virtual void OnEvent(AppEngine::Event& event) override {
   };

   UIFrame* m_uiMainFrame;
   AppData m_appData;

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


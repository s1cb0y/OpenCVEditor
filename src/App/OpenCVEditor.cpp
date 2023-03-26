#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
#include "App/UI/UITools.h"
#include "App/UI/UIMenuBar.h"
#include "AppEngine/UI/UIFrame.h"
#include "AppEngine/Log.h"
//#include <opencv2/opencv.hpp>



class MainLayer : public AppEngine::Layer {
public:
   MainLayer() : AppEngine::Layer("MainLayer") {
      UITools* uiTools = new UITools();
      UIMenuBar* uiMenuBar = new UIMenuBar();
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
      std::stringstream ss;
      ss << "Event : " << event.GetName();
      LOG_INFO(ss.str());
   };

   UIFrame* m_uiMainFrame;
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


#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "imgui.h"
#include "App/UI/Components/UITools.h"
#include "App/UI/Components/UIMenuBar.h"
#include "AppEngine/UI/UIFrame.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"
#include "App/OpenCV/OpenCVFile.h"



class MainLayer : public AppEngine::Layer {
public:
   MainLayer() : AppEngine::Layer("MainLayer") {
      UITools* uiTools = new UITools(&m_appData);
      UIMenuBar* uiMenuBar = new UIMenuBar(&m_appData);
      m_uiMainFrame = new UIFrame("OpenCV Editor", ImGuiWindowFlags_MenuBar);
      m_uiMainFrame->AddWidget(uiMenuBar);
      m_uiMainFrame->AddWidget(uiTools);
      m_appData.ImageFileString().Subscribe(BIND_FN(MainLayer::OnFilePathChanged));
      m_Image = nullptr;
   }

   ~MainLayer() {
      if (m_uiMainFrame)
         delete m_uiMainFrame;
   }

   virtual void OnImGuiRender() override {
      m_uiMainFrame->Render();
   }

   virtual void OnEvent(AppEngine::Event& event) override {
   };

   virtual void OnUpdate() override {
      if(m_Image)
         m_Image->Render();
   }
private:
   void OnFilePathChanged(std::string& path) {
      if (m_Image) {
         delete m_Image;
         m_Image = nullptr;
      }
      m_Image = new CVImage(path);
   }
private:   

   UIFrame* m_uiMainFrame;
   AppData m_appData;
   CVImage* m_Image;

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


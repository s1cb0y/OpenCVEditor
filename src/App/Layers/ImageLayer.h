#pragma once

#include "AppEngine/Core.h"
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Events/ImageEvent.h"
#include "App/UI/Components/UITools.h"
#include "App/UI/Components/UIMenuBar.h"
#include "AppEngine/UI/UIFrame.h"
#include "App/AppData/AppData.h"
#include "App/OpenCV/ImageOperationStack.h"

class ImageLayer : public AppEngine::Layer {
public:
   ImageLayer(AppData* appData) : AppEngine::Layer("ImageLayer") {
      m_AppData = appData;
      UITools* uiTools     = new UITools(m_AppData);
      UIMenuBar* uiMenuBar = new UIMenuBar(m_AppData);
      m_UiMainFrame        = new UIFrame("OpenCV Editor", ImGuiWindowFlags_MenuBar);
      m_UiMainFrame->AddWidget(uiMenuBar);
      m_UiMainFrame->AddWidget(uiTools);     
   }

   ~ImageLayer() {
      if (m_UiMainFrame)
         delete m_UiMainFrame;         
   }

   virtual void OnImGuiRender() override {      
      m_UiMainFrame->Render();
   }

   virtual void OnEvent(AppEngine::Event& event) override {
      AppEngine::EventDispatcher dispatcher(event);
      dispatcher.Dispatch<AppEngine::OpenImageEvent>(BIND_FN(ImageLayer::OnOpenImage));
      dispatcher.Dispatch<AppEngine::CloseImageEvent>(BIND_FN(ImageLayer::OnCloseImage));
   };

   virtual void OnUpdate() override {
      if (m_AppData->GetImage()){
         m_AppData->GetImage()->Render();
      }
   }
private:
   
   bool OnOpenImage(AppEngine::OpenImageEvent& e) {
      LOG_INFO("Open image: {}", e.GetPath());
      m_AppData->SetImage(new CVImage(e.GetPath()));
      return true;
   }
   bool OnCloseImage(AppEngine::CloseImageEvent& e) {
      LOG_INFO("Close current image");
      m_AppData->SetImage(nullptr);
      return true;
   }

private:

   UIFrame* m_UiMainFrame;
   AppData* m_AppData;
};
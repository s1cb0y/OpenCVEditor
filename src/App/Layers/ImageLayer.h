#pragma once

#include "AppEngine/Core.h"
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Events/ImageEvent.h"
#include "AppEngine/Events/MouseEvent.h"
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
      dispatcher.Dispatch<AppEngine::MouseButtonPressedEvent>(BIND_FN(ImageLayer::OnShowImageCoords));
      dispatcher.Dispatch<AppEngine::MouseMovedEvent>(BIND_FN(ImageLayer::OnStoreImageCoords));
      
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

   bool OnShowImageCoords(AppEngine::MouseButtonPressedEvent& e) {
      LOG_INFO("Mouse clicked at image position (x : {}, y : {})", m_image_coord_x, m_image_coord_y );
      //m_AppData->GetImage()->GetOriginalData().at<cv::Vec3b>(m_image_coord_x, m_image_coord_y) = {0,0,0};            
      return true;
   }

   bool OnStoreImageCoords(AppEngine::MouseMovedEvent& e) {
      
      m_image_coord_x = e.GetX();
      m_image_coord_y = e.GetY();
      return true;
   }


private:
   uint32_t m_image_coord_x;
   uint32_t m_image_coord_y;
   UIFrame* m_UiMainFrame;
   AppData* m_AppData;
};

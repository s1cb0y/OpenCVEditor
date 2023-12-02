#pragma once

#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"
#include "AppEngine/Events/ImageProcessingEvent.h"

#include "App/AppData/AppData.h"
#include "App/OpenCV/Filters.h"


class ImageProcessingLayer : public AppEngine::Layer {
public:
   ImageProcessingLayer(AppData* appData) : AppEngine::Layer("ImageProcessingLayer") {
      m_appData = appData;
   }

   ~ImageProcessingLayer() {
   }
      
   virtual void OnEvent(AppEngine::Event& event) override {
      AppEngine::EventDispatcher dispatcher(event);
      dispatcher.Dispatch<AppEngine::AddImageProcessingOperationEvent>(BIND_FN(ImageProcessingLayer::OnAddImageProcessingOperation));
      dispatcher.Dispatch<AppEngine::DeleteImageProcessingOperationEvent>(BIND_FN(ImageProcessingLayer::OnDeleteImageProcessingOperation));
   };

   virtual void OnUpdate() override {
   }
private:
 
   bool OnAddImageProcessingOperation(AppEngine::AddImageProcessingOperationEvent& e) {
      LOG_INFO("Added new image processing operation: {}", e.GetName());
      if (e.GetName() == "GaussianBlur") {
         m_appData->GetImageOperationStack().PushOperation(new GaussianBlurFilter(4, 0)); 
      }
      
      return true;
   }
   bool OnDeleteImageProcessingOperation(AppEngine::DeleteImageProcessingOperationEvent& e) {
      LOG_INFO("Deleted image processing operation: {}", e.GetName());
      return true;
   }

private:
   AppData* m_appData;

};


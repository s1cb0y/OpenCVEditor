#pragma once
#include "AppEngine/UI/UISection.h"
#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
#include "App/OpenCV/Filters.h"
#include "AppEngine/Events/ApplicationEvent.h"
#include "AppEngine/Events/ImageProcessingEvent.h"

class UIFilters : public UIWidget {

public:

   UIFilters(AppData* appData) : UIWidget("Filters") {
      m_AppData = appData;
   }
   
   ~UIFilters(){}

private:
   virtual void RenderImpl() override {

      if (ImGui::TreeNode("Filters")){
         /* ----------- Gaussian Blur ---------------------*/
         static bool checkGaussian = false;
         static bool oldCheckGaussian = checkGaussian;
         ImGui::Checkbox("Gaussian", &checkGaussian); ImGui::SameLine();
         static int gaussianSize = 9;
         ImGui::InputInt("Kernel Size", &gaussianSize, 2);  
         if (checkGaussian != oldCheckGaussian) {
            oldCheckGaussian = checkGaussian;
            if (checkGaussian) {
               AppEngine::AddImageProcessingOperationEvent event = AppEngine::AddImageProcessingOperationEvent("Gaussian Filter");
               AppEngine::Application::Get().OnEvent(event);
               if (gaussianSize % 2)
                  OpenCVFilters::GaussianBlur(m_AppData->GetImage(), gaussianSize);
               else
                  LOG_ERROR("Please select an odd size for gaussian blur filter")               
            }
         }
         ImGui::TreePop();
      }
   }   

   AppData* m_AppData = nullptr;
};
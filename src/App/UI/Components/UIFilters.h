#pragma once
#include "AppEngine/UI/UISection.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"
#include "App/OpenCV/Filters.h"
class UIFilters : public UIWidget {

public:

   UIFilters(AppData* appData) : UIWidget("Filters") {
      m_AppData = appData;
   }
   
   ~UIFilters(){}
private:
   virtual void RenderImpl() override {

      if (ImGui::TreeNode("Filters")){
         static bool checkGaussian = false;
         ImGui::Checkbox("Gaussian", &checkGaussian); ImGui::SameLine();
         static int gaussianSize = 9;
         ImGui::InputInt("Kernel Size", &gaussianSize, 2);  
         if (checkGaussian) {
            if (gaussianSize % 2)
               OpenVCFilters::GaussianBlur(m_AppData->GetImage(), gaussianSize);
            else
               LOG_ERROR("Please select an odd size for gaussian blur filter")
               checkGaussian = false;   
         }
         ImGui::TreePop();
      }
   }   
};
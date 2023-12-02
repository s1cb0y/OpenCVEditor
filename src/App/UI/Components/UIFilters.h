#pragma once
#include "AppEngine/UI/UISection.h"
#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
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
         /* ----------- Gaussian Blur ---------------------*/
         static bool checkGaussian = false;
         static bool oldCheckGaussian = checkGaussian;
         ImGui::Checkbox("Gaussian", &checkGaussian); ImGui::SameLine();
         static int gaussianSize = 9;
         ImGui::InputInt("Kernel Size", &gaussianSize, 2);  
         if (checkGaussian != oldCheckGaussian) {
            oldCheckGaussian = checkGaussian;
            if (checkGaussian) {
               m_AppData->GetImageOperationStack().PushOperation(new GaussianBlurFilter(gaussianSize, 0));
               m_AppData->GetImageOperationStack().ProcessImage(m_AppData->GetImage());
            }
         }
         ImGui::TreePop();
      }
   }   

   AppData* m_AppData = nullptr;
};
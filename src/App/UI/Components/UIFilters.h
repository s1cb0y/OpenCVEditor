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
         static bool oldCheckGaussian = false;
         static int op_id = 0;
         ImGui::Checkbox("Gaussian", &checkGaussian); ImGui::SameLine();
         static int gaussianSize = 9;
         ImGui::InputInt("Kernel Size", &gaussianSize, 2);  
         if (checkGaussian != oldCheckGaussian) {
            oldCheckGaussian = checkGaussian;
            if (checkGaussian) {
               op_id = m_AppData->GetImageOperationStack().PushOperation(new GaussianBlurFilter(gaussianSize, 0));               
            } else {
               // delete operations
               m_AppData->GetImageOperationStack().PopOperation(op_id);
            }
         }
         ImGui::TreePop();
      }
   }   

   AppData* m_AppData = nullptr;
};
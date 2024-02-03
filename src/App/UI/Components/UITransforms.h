#pragma once
#include "AppEngine/UI/UISection.h"
#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
#include "App/OpenCV/ImageOperations/Transformations.h"

class UITransforms : public UIWidget {

public:

   UITransforms(AppData* appData) : UIWidget("Transformations") {
      m_AppData = appData;
   }
   
   ~UITransforms(){}

private:
   virtual void RenderImpl() override {

      if (ImGui::TreeNode("Transformations")){
         /* ----------- Flip  ------------*/
         static bool checkFlip = false;
         static bool oldcheckFlip = false;
         static int op_id = 0;
         ImGui::Checkbox("Flip", &checkFlip); ImGui::SameLine();
         FlipTransformation::FLIP_MODE flipMode = FlipTransformation::X_AXIS;
         //ImGui::Combo("Flip Mode", &gaussianSize, 2);  
         if (checkFlip != oldcheckFlip) {
            oldcheckFlip = checkFlip;
            if (checkFlip) {
               op_id = m_AppData->GetImageOperationStack().PushOperation(new FlipTransformation(flipMode));
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
#pragma once
#include "AppEngine/UI/UISection.h"
#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
#include "App/OpenCV/ImageOperations/Transformations.h"
#include <map>

const std::map<const char*, FlipTransformation::FLIP_MODE> STR_TO_FLIP_MODE = {
                                                                                   {"X_AXIS" , FlipTransformation::X_AXIS},
                                                                                   {"Y_AXIS" , FlipTransformation::Y_AXIS},
                                                                                   {"XY_AXIS", FlipTransformation::XY_AXIS}
};

class UITransforms : public UIWidget {

public:

   UITransforms(AppData* appData) : UIWidget("Transformations") {
      m_AppData = appData;
   }

   ~UITransforms() {}

private:
   virtual void RenderImpl() override {

      if (ImGui::TreeNode("Transformations")) {
         RenderFlip();
         ImGui::TreePop();
      }
   }


   void RenderFlip() {
      
      static bool checkFlip = false;
      static bool oldcheckFlip = false;
      
      const char* m_FlipModes[] = { "X_AXIS", "Y_AXIS" , "XY_AXIS" };
      ImGui::Checkbox("Flip", &checkFlip); ImGui::SameLine();

      static int current_item = 0;
      ImGui::Combo("combo 3 (array)", &current_item, m_FlipModes, IM_ARRAYSIZE(m_FlipModes));
      
      if (checkFlip != oldcheckFlip) {
         oldcheckFlip = checkFlip;
         static int op_id = 0;
         if (checkFlip) {
            op_id = m_AppData->GetImageOperationStack().PushOperation(new FlipTransformation(STR_TO_FLIP_MODE.at(m_FlipModes[current_item])));
         }
         else {
            // delete operations
            m_AppData->GetImageOperationStack().PopOperation(op_id);
         }
      }
   }

   

   AppData* m_AppData = nullptr;
};
#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
#include "App/UI/Components/UIFilters.h"
#include "App/UI/Components/UITransforms.h"

class UITools : public UIWidget {

public:

   UITools(AppData* appData) : UIWidget("Tools") {
      m_AppData = appData;
      m_UiFilters = new UIFilters(appData);
      m_UiTransforms = new UITransforms(appData);
   }
   ~UITools(){
      delete m_UiFilters;
      delete m_UiTransforms;
   }

private:

   virtual void RenderImpl() override {
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      if (m_AppData->GetImage())
         ImGui::Text("Currently selected file: %s", + m_AppData->GetImage()->GetFilePath().c_str());
      else
         ImGui::Text("Please start by opening a new image file to process (File -> Open)");
      ImGui::Text("=================================");
      ImGui::Text("========== Tools section =============");
     
      m_UiFilters->Render();
      m_UiTransforms->Render();
      
   }

   
private:
   AppData* m_AppData;
   UIFilters* m_UiFilters;
   UITransforms* m_UiTransforms;

};


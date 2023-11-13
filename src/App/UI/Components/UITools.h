#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"
#include "App/UI/Components/UIFilters.h"
#include "App/OpenCV/Filters.h"

class UITools : public UIWidget {

public:

   UITools(AppData* appData) : UIWidget("Tools") {
      m_AppData = appData;
      m_ImageFilePath = "";
      m_AppData->ImageFileString().Subscribe(BIND_FN(UITools::DispayFilePath));
      m_UiFilters = new UIFilters(appData);
   }
   ~UITools(){}

private:

   virtual void RenderImpl() override {
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      if (m_ImageFilePath.empty()) 
         ImGui::Text("Please start by opening a new image file to process (File -> Open)");
      else
         ImGui::Text("Currently selected file: %s", + m_ImageFilePath.c_str());
      ImGui::Text("=================================");
      ImGui::Text("========== Tools section =============");
     
      m_UiFilters->Render();
   }

   void DispayFilePath(std::string& path){
      m_ImageFilePath = path;
   }
private:
   AppData* m_AppData;
   std::string m_ImageFilePath;
   UIFilters* m_UiFilters;
};


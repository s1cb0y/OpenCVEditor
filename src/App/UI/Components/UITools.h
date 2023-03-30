#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"

class UITools : public UIWidget {

public:

   UITools(AppData* appData) : UIWidget("Tools") {
      m_AppData = appData;
      m_ImageFilePath = "No file was selected!";
      m_AppData->ImageFileString().Subscribe(BIND_FN(UITools::DispayFilePath));
   }
   ~UITools(){}

private:

   virtual void RenderImpl() override {
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      ImGui::Text("Please start by opening a new image file to process (File -> Open)");
          

      ImGui::Text(m_ImageFilePath.c_str());
   }

   void DispayFilePath(std::string& path){
      m_ImageFilePath = path;
   }
private:
   AppData* m_AppData;
   std::string m_ImageFilePath;
};


#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "App/UI/AppData/AppData.h"

class UITools : public UIWidget {

public:

   UITools(AppData* appData) : UIWidget("Tools") {
      m_AppData = appData;
      m_ImageFilePath = "";
      m_AppData->ImageFileString().Subscribe(BIND_FN(UITools::DispayFilePath));
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
      ImGui::Text("Filters and Morphs");
      if (ImGui::TreeNode("Filters")){
     
         static bool checkGaussian = false;
         ImGui::Checkbox("Gaussian", &checkGaussian);
         static int gaussianSize = 45;
         ImGui::InputInt("Kernel Size", &gaussianSize);  ImGui::SameLine();
         if (checkGaussian) {
            Filter(gaussianSize);
         }
         ImGui::TreePop();
      }

   }
   void Filter(int size) {
      CVImage *image = m_AppData->GetImage();
      if (image)
         cv::GaussianBlur(image->GetData(), image->GetData(), cv::Size(size, size), 0);
   }


   void DispayFilePath(std::string& path){
      m_ImageFilePath = path;
   }
private:
   AppData* m_AppData;
   std::string m_ImageFilePath;
};


#pragma once
#include "AppEngine/UI/UIFrame.h"
class UIMainFrame : public UIFrame {

public:

   UIMainFrame() : UIFrame("OpenCV Editor", ImGuiWindowFlags_MenuBar) {}
   ~UIMainFrame()
   {
   }

private:

   virtual void RenderImpl() override {
      ImGui::Text("Hello, welcome to OpenCV Editor");
      ImGui::Text("=================================");
      ImGui::Text("Please start by opening a new image file to process (File -> Open");
   }
};
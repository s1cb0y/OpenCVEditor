#pragma once
#include "App/UI/UIWidget.h"
#include "AppEngine/Log.h"
class UITools : public UIWidget {

public:

   UITools() : UIWidget("Tools") {}
   ~UITools()
   {
   }

   virtual void RenderImpl() override {
      ImGui::Text("Here are your tools!");
   }
};


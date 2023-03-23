#pragma once
#include "App/UI/UIWidget.h"
#include "AppEngine/Log.h"

class UIMenuBar : public UIWidget {

public:

   UIMenuBar() : UIWidget("MenuBar") {}
   ~UIMenuBar()
   {
   }

   virtual void RenderImpl() override {
      ImGui::Text("Here are your tools!");
   }
};


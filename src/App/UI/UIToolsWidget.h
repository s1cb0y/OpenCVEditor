#include "App/UI/UIWidget.h"
#include "AppEngine/Log.h"
class UIToolsWidget : public UIWidget {

public:

   UIToolsWidget() : UIWidget("Tools") {}
   ~UIToolsWidget()
   {
   }

   virtual void RenderImpl() override {
      ImGui::Text("Here are your tools!");
   }
};


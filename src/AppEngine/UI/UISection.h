#pragma once
#include "AppEngine/Core.h"
#include "AppEngine/UI/UIWidget.h"
#include "imgui.h"

class UISection : public UIWidget {

public:
   UISection(const std::string& name, bool show = true) : UIWidget(name, show) {}
   void AddWidget(UIWidget* widget) {
      m_widgets.push_back(widget);
   }
   ~UISection() override {
      for (auto w : m_widgets) {
         if (w)
            delete w;
      }
   }

private:
   void RenderImpl() override {
      std::string text = "******" + Name() + "******";
      ImGui::Text(text.c_str());
      for (auto w : m_widgets) {
         w->Render();
      }
   }
   std::vector<UIWidget*> m_widgets;
   
};
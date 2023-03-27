#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "imgui.h"

class UIFrame : public UIWidget {

public:
   UIFrame(const std::string& name, ImGuiWindowFlags flags, bool show = true) : UIWidget(name, show) {}
   void AddWidget(UIWidget* widget) {
      m_widgets.push_back(widget);
   }
   ~UIFrame() override {
      for (auto w : m_widgets) {
         if (w)
            delete w;
      }
   }

private:
   void RenderImpl() override {
      bool show = IsVisible();
      if (!ImGui::Begin(Name().c_str(), &show, ImGuiWindowFlags_MenuBar)) // TODO Fix this const flag
      {
         // Early out if the window is collapsed, as an optimization.
         LOG_ERROR(printf("Error in UIFrame %s, could not begin window", Name().c_str()));
         ImGui::End();
         return;
      }

      for (auto w : m_widgets) {
         w->Render();
      }
      ImGui::End();
   }
   std::vector<UIWidget*> m_widgets;
   ImGuiWindowFlags m_flags;
   
};
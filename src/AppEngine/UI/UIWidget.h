#pragma once
#include "AppEngine/Core.h"
#include "imgui.h"

class UIWidget {
public:
   UIWidget(const std::string& name, bool show = true) : name(name), show(show) {}

   void Show() { show = true; };
   void Hide() { show = false; };
   bool IsVisible() { return show; }
   void Render() {
      if (show)
         RenderImpl();
   };
   const std::string& Name() const { return name; }

private:
   virtual void RenderImpl() = 0;
   
   std::string name;
   bool show;
};
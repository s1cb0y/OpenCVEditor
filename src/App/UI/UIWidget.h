#pragma once
#include "AppEngine/Core.h"
#include "imgui.h"

class UIWidget {
public:
   UIWidget(const std::string& name, bool show = false) : name( name ), show(show) {}

   void Show() { show = true; };
   void Hide() { show = false; };
   void Render() {
      if (show)
         RenderImpl();
   };
   virtual void RenderImpl() = 0;
private:
   std::string name;
   bool show;
};
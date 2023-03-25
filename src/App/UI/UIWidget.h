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

private:
   virtual void RenderImpl() = 0;
   
   std::string name;
   bool show;
};
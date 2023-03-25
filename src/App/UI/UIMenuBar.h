#pragma once
#include "App/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "PFD.h"

class UIMenuBar : public UIWidget {

public:

   UIMenuBar() : UIWidget("MenuBar") {}
   ~UIMenuBar()
   {
   }

private:

   virtual void RenderImpl() override {// Menu Bar
      if (ImGui::BeginMenuBar())
      {       
         if (ImGui::BeginMenu("File"))
         {           
            if (ImGui::MenuItem("Open", "Ctrl+O")) { OpenFile();}
            ImGui::EndMenu();
         }         
         ImGui::EndMenuBar();
      }
   }

   void OpenFile()
   {
      // File open
      auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                              { "Image Files (.png .jpeg .jpg)", "*.png *.jpeg *.jpg",
                                 "All Files", "*" },
                              pfd::opt::none);
      std::cout << "Selected file:";
      for (auto const &name : f.result())
         std::cout << " " + name;
      std::cout << "\n";
   }

   bool m_showOpenDialog;   
};


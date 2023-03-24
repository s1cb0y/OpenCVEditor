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

   virtual void RenderImpl() override {// Menu Bar
      if (ImGui::BeginMenuBar())
      {       
         if (ImGui::BeginMenu("File"))
         {           
            if (ImGui::MenuItem("Open", "Ctrl+O")) { test_open_file();}
            ImGui::EndMenu();
         }         
         ImGui::EndMenuBar();
      }
   }
private:

   void test_open_file()
   {
      // File open
      auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                              { "Text Files (.txt .text)", "*.txt *.text",
                                 "All Files", "*" },
                              pfd::opt::multiselect);
      std::cout << "Selected files:";
      for (auto const &name : f.result())
         std::cout << " " + name;
      std::cout << "\n";
   }

   bool m_showOpenDialog;   
};


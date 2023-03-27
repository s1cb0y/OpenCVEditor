#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "PFD.h"
#include "App/UI/AppData/AppData.h"
class UIMenuBar : public UIWidget {

public:

   UIMenuBar(AppData* appData) : UIWidget("MenuBar") 
   {
      m_AppData = appData;
   }

   ~UIMenuBar()
   {
   }

private:

   virtual void RenderImpl() override {
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
      for (auto const &name : f.result()){
         std::cout << " " + name;
         m_AppData->ImageFileString().Set(name);
      }
      std::cout << "\n";
      
   }

private:
   AppData* m_AppData;
};


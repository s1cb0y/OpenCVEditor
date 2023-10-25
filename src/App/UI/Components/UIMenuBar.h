#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "PFD.h"
#include "App/UI/AppData/AppData.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"

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
           // if (ImGui::MenuItem("Close App", "Ctrl+X")) { CloseApp(); }
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
      if (!f.result().empty()) 
         m_AppData->ImageFileString().Set(f.result()[0]); // update observable
   }

private:
   AppData* m_AppData;
};


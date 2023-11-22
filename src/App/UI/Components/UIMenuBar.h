#pragma once
#include "AppEngine/UI/UIWidget.h"
#include "AppEngine/Log.h"
#include "PFD.h"
#include "App/AppData/AppData.h"
#include "AppEngine/Application.h"
#include "AppEngine/Events/Event.h"

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
            if (ImGui::MenuItem("Open", "Ctrl+O")) { OpenFile(); }
            if (ImGui::MenuItem("Close App", "Ctrl+X")) { CloseApp(); }
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
      if (!f.result().empty()) {
         AppEngine::OpenImageEvent event(f.result()[0]);
         AppEngine::Application::Get().OnEvent(event);         
        // m_AppData->ImageFileString().Set(f.result()[0]); // update observable
      }
   }

   void CloseApp(){
      AppEngine::WindowCloseEvent event;
      AppEngine::Application::Get().OnEvent(event);
   }
   

private:
   AppData* m_AppData;
};


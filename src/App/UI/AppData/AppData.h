#pragma once
#include "AppEngine/Core.h"
#include "AppEngine/Observables/Observables.h"
#include "App/OpenCV/OpenCVFile.h"

class AppData
{
   public:
      AppData() : m_ImageFilePath(""), m_Image(nullptr){
      }
      ~AppData() {
         if (m_Image) {
            delete m_Image;
            m_Image = nullptr;
         }
      }
      Observable<std::string>& ImageFileString() { return m_ImageFilePath;}
      void SetImage(CVImage* image) { 
         m_Image = image; 
      }
      CVImage* GetImage() { return m_Image; }

   private:
      Observable<std::string> m_ImageFilePath;
      CVImage* m_Image;
       
};
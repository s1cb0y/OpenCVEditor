#pragma once
#include "AppEngine/Core.h"
#include "AppEngine/Observables/Observables.h"
#include "App/OpenCV/OpenCVImage.h"
#include "App/OpenCV/ImageOperations/ImageOperationStack.h"

class AppData
{
public:
   AppData() : m_ImageFilePath(""), m_Image(nullptr){}

   ~AppData() {
      if (m_Image) {
         delete m_Image;
         m_Image = nullptr;
      }         
   }
   Observable<std::string>& ImageFileString() { return m_ImageFilePath;}
   void SetImage(CVImage* image) { 
      m_Image = image; 
      m_ImageOperationStack.SetImage(image);
   }
   CVImage* GetImage() { return m_Image; }
   ImageOperationStack& GetImageOperationStack() { return m_ImageOperationStack; }

private:
   Observable<std::string> m_ImageFilePath;
   CVImage* m_Image;
   ImageOperationStack m_ImageOperationStack;
};
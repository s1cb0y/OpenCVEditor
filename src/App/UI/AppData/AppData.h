#pragma once
#include "AppEngine/Core.h"
#include "AppEngine/Observables/Observables.h"
#include "App/OpenCV/OpenCVFile.h"

class AppData
{
   public:
      AppData() : m_ImageFilePath(""){}
      Observable<std::string>& ImageFileString() { return m_ImageFilePath;}
   private:
      Observable<std::string> m_ImageFilePath = Observable<std::string>("");
       
};
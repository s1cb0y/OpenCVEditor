#include "AppEngine/Application.h"


class OpenCVEditor : public AppEngine::Application {
public:
   OpenCVEditor() : AppEngine::Application()
   {
   }

};

AppEngine::Application* AppEngine::CreateApplication(){
   return new OpenCVEditor();
}


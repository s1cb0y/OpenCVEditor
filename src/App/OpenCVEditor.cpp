#include "AppEngine/Core.h"
#include "AppEngine/Application.h"
#include "AppEngine/Layer/Layer.h"



#include "AppEngine/Log.h"
#include "App/AppData/AppData.h"
#include "App/OpenCV/OpenCVImage.h"
// Layers
#include "App/Layers/ImageLayer.h"


class OpenCVEditor : public AppEngine::Application {
public:
   OpenCVEditor() : AppEngine::Application()
   {
      PushLayer(new ImageLayer(&m_AppData));
   }
   AppData m_AppData;
};

AppEngine::Application* AppEngine::CreateApplication(){
   return new OpenCVEditor();
}


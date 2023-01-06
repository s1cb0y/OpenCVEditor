#pragma once
#include "AppEngine/Core.h"

namespace AppEngine{

   struct WindowProps
	{
		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& title = "OpenCVEditor AppEngine", 
					unsigned int w = 1280, 
					unsigned int h = 720)
			: Height{h}, Width{w}, Title{title}
		{
		}
	};

   class Window{
   public:
      virtual ~Window() = default;

      virtual unsigned int GetWidth() = 0;
      virtual unsigned int GetHeigth() = 0;

      virtual void OnUpdate() = 0;

	  virtual void* GetNativeWindow() const = 0;

      static Window* Create(const WindowProps& props);
   };

}
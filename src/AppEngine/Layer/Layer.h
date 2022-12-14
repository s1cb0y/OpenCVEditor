#pragma once
#include "AppEngine/Core.h"
#include "AppEngine/Events/Event.h"

namespace AppEngine{
   class Layer{

   public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer() = default;

      virtual void OnAttach(){};
      virtual void OnDetach(){};
      virtual void OnUpdate(){};
      virtual void OnImGuiRender(){};
      virtual void OnEvent(Event& event){};
      inline std::string GetName() const {return m_debugName;};
   private:
      std::string m_debugName;
   };
}
#pragma once
#include "AppEngine/Layer/Layer.h"

namespace AppEngine{
   class ImGuiLayer : public Layer {
   public:
      ImGuiLayer();
      ~ImGuiLayer();

      virtual void OnAttach() override;
      virtual void OnDetach() override;

      virtual void OnImGuiRender() override;

      void Begin();
      void End();

   };
}
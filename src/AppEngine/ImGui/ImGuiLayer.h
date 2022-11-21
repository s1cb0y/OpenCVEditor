#pragma once
#include "AppEngine/Layer/Layer.h"

namespace AppEngine{
   class ImGuiLayer : public Layer {
   public:
      ImGuiLayer();
      ~ImGuiLayer() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;

      virtual void OnUpdate() override ;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Event& event) override;

      void Begin();
      void End();

   }
}
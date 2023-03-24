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
      virtual void OnEvent(Event& event) override;

      void Begin();
      void End();
   private:
      bool m_BlockEvents;
   };
}
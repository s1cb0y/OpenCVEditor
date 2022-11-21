#pragma once

#include "AppEngine/Layer/Layer.h"

namespace AppEngine{
   class LayerStack{
   public: 
      LayerStack() = default;
      ~LayerStack();
      void PushLayer(Layer* layer);
      void PopLayer(Layer* layer);
      void PushOverlay(Layer* layer);
      void PopOverlay(Layer* layer);
   private:
      std::vector<Layer*> m_layers;
      unsigned int m_layerInsertIndex = 0;
   };
}
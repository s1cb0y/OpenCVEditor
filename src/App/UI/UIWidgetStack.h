#pragma once
#include "AppEngine/Core.h"
#include "App/UI/UIWidget.h"

class UIWidgetStack {
public:
   void PushWidget(UIWidget* widget);
   void PopWidget(UIWidget* widget);

   std::iterator
private:
   std::vector<UIWidget*> m_stack;

};
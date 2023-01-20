#pragma once

#include "AppEngine/Events/Event.h"

namespace AppEngine{
   
   class WindowCloseEvent : public Event {
   public:
      WindowCloseEvent(){};
      EVENT_CLASS_TYPE(WindowClose);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
   };

   class WindowResizeEvent : public Event {
      int m_Width;
      int m_Height;

   public:
      WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {};
      int GetWidth() { return m_Width; }
      int GetHeight() { return m_Height; };
      EVENT_CLASS_TYPE(WindowResize);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
   };

}
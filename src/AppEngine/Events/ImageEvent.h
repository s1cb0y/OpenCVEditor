#pragma once

#include "AppEngine/Events/Event.h"

namespace AppEngine{

   class OpenImageEvent : public Event {
      std::string m_FilePath;
   public:
      OpenImageEvent(const std::string& path) : m_FilePath(path) {};
      std::string& GetPath() { return m_FilePath; }
      EVENT_CLASS_TYPE(OpenImage);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImage);
   };

   class CloseImageEvent : public Event {
   public:
      CloseImageEvent() {};
      EVENT_CLASS_TYPE(CloseImage);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImage);
   };

}
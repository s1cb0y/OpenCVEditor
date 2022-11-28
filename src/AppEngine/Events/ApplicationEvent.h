#pragma once

#include "AppEngine/Events/Event.h"

namespace AppEngine{
   
   class WindowCloseEvent : public Event {
   public:
      WindowCloseEvent(){};
      EVENT_CLASS_TYPE(WindowClose);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
   };

}
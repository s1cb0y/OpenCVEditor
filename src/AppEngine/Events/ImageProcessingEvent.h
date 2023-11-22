#pragma once

#include "AppEngine/Events/Event.h"

namespace AppEngine{

   class AddImageProcessingOperationEvent : public Event {
      std::string m_Name;
   public:
      AddImageProcessingOperationEvent(const std::string& name) : m_Name(name) {};
      std::string& GetName() { return m_Name; }
      EVENT_CLASS_TYPE(AddImageProcessingOperation);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImageProcessing);
   };

   class DeleteImageProcessingOperationEvent : public Event {
      std::string m_Name;
   public:
      DeleteImageProcessingOperationEvent(const std::string& name) : m_Name(name) {};
      std::string& GetName() { return m_Name; }
      EVENT_CLASS_TYPE(DeleteImageProcessingOperation);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImageProcessing);
   };

}
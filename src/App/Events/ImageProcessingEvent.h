#pragma once

#include "AppEngine/Events/Event.h"

namespace AppEngine{

   class AddImageProcessingOperationEvent : public Event {
      int m_OperationType;
   public:
      AddImageProcessingOperationEvent(int operationType) : m_OperationType(operationType) {};
      int GetType() { return m_OperationType; }
      EVENT_CLASS_TYPE(AddImageProcessingOperation);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImageProcessing);
   };

   class DeleteImageProcessingOperationEvent : public Event {
      int m_OperationType;
   public:
      DeleteImageProcessingOperationEvent(int operationType) : m_OperationType(operationType) {};
      int GetType() { return m_OperationType; }
      EVENT_CLASS_TYPE(DeleteImageProcessingOperation);
      EVENT_CLASS_CATEGORY(EventCategory::EventCategoryImageProcessing);
   };

}
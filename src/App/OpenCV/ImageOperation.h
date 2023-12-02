#pragma once

#include "AppEngine/Core.h"
#include "App/OpenCV/OpenCVImage.h"
enum class OperationType
{
   None = 0,
   Filter
};

enum class OperationCategory
{
   OperationCategoryIrreversible,
   OperationCategoryReversible,
   EventCategoryImageProcessing
};

class ImageOperation {
public:
   virtual ~ImageOperation() = default;
   virtual OperationType GetOperationType() const = 0;
   virtual const char* GetName() const = 0;
   virtual OperationCategory GetOperationCategory() const = 0;
   virtual std::string ToString() const { return GetName(); }

   virtual void Process(CVImage* image) = 0;
};

